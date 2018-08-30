///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017-2018 Ansersion
/// 
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// 
///     http://www.apache.org/licenses/LICENSE-2.0
/// 
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// @file 	bp_make_payload.c
/// @brief 	functions to make payload for BP packet source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_make_payload.h>
#include <bp_public.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_sig_table.h>
#include <bp_custom_sig_table.h>


// std
#ifdef DEBUG
#include <stdio.h>
#endif
// #include <string.h>
#include <bp_strlen.h>

#define MAX_GET_ACK_SIG_NUM 	64
BP_SigType g_SigTypeArray[MAX_GET_ACK_SIG_NUM];
BP_SigId2Val g_SigArray[MAX_GET_ACK_SIG_NUM];


BP_UINT8 * make_pld_cnct(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);
BP_UINT8 * make_pld_postack(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);
BP_UINT8 * make_pld_getack(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);
BP_UINT8 * make_pld_rprt(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);
BP_UINT8 * make_pld_ping(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);

BP_UINT8 * BP_make_payload(BP_UINT8 * pack, BPPackPayload * payload, BP_UINT8 bp_type, BPPackVrbHead * vrb_head)
{
	if(BP_NULL == pack) {
		return BP_NULL;
	}

	if(BP_NULL == payload) {
		return BP_NULL;
	}

	switch(bp_type) {
		case BP_PACK_TYPE_CONNECT: 	
#ifdef DEBUG
			printf("BP_make_payload: CONNECT\n");
#endif
			pack = make_pld_cnct(pack, payload, vrb_head);
			break;
		case BP_PACK_TYPE_CONNACK: 	
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_GET: 		
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_GETACK: 	
			pack = make_pld_getack(pack, payload, vrb_head);
			break;
		case BP_PACK_TYPE_POST: 		
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_POSTACK: 	
			pack = make_pld_postack(pack, payload, vrb_head);
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_REPORT: 	
			pack = make_pld_rprt(pack, payload, vrb_head);
			break;
		case BP_PACK_TYPE_RPRTACK: 	
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PING: 		
			pack = make_pld_ping(pack, payload, vrb_head);
			break;
		case BP_PACK_TYPE_PINGACK: 	
			// No payload
			break;
		case BP_PACK_TYPE_PUSH:
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PUSHACK:
			// printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_DISCONN:
			// No payload
			break;
		default:
			// printf("Err: unsupported BP type: %d\n", bp_type);
			break;
	}

	return pack;
}

BP_UINT8 * make_pld_cnct(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	BP_UINT8 * oldPack = pack;
	BP_UINT32 i;
#ifdef DEBUG
	printf("name=%s, len=%d\n", payload->u.CONNECT.Name, payload->u.CONNECT.NameLen);
	printf("password=%s, len=%d\n", payload->u.CONNECT.Pwd, payload->u.CONNECT.PwdLen);
#endif

	pack = BP_Set2ByteField(pack, payload->u.CONNECT.Name, payload->u.CONNECT.NameLen);
	pack = BP_Set2ByteField(pack, payload->u.CONNECT.Pwd, payload->u.CONNECT.PwdLen);
	// if(pack == BP_NULL) {
	// 	printf("pack == BP_NULL\n");
	// }
	// for(i = 0; i < payload->u.CONNECT.NameLen + payload->u.CONNECT.PwdLen + 4; i++) {
	// 	printf("%x ", oldPack[i]);
	// }
	// printf("\n");
	//*pack++ = payload->u.CONNECT.ClntIdLen;
	//pack = BP_SetNet16(pack, payload->u.CONNECT.ClntId);
	return pack;
}

BP_UINT8 * make_pld_getack(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	BP_UINT16 i, j;
	BP_UINT16 t4n = 0, t2n = 0, txn = 0;
	const BP_UINT8 * sig_map;
	BP_UINT8 * pack_4 = BP_NULL;
	BP_UINT8 * pack_2 = BP_NULL;
	BP_UINT8 * pack_x = BP_NULL;
	if(vrb_head->u.GETACK.Flags & BP_VRB_FLAG_SIG_SET_MSK) {
		// not supported
		return BP_NULL;
	}
	// printf("make_pld_getack: %d\n", payload->u.GETACK.SigNum);
	for(i = 0; i < payload->u.GETACK.SigNum; i++) {
		switch(payload->u.GETACK.SigTypeArray[i]) {
			case SIG_TYPE_U32:
			case SIG_TYPE_I32:
			case SIG_TYPE_FLT:
				t4n++;
				break;
			case SIG_TYPE_U16:
			case SIG_TYPE_I16:
			case SIG_TYPE_ENM:
				t2n++;
				break;
			case SIG_TYPE_STR:
				txn++;
				break;
			default:
				return BP_NULL;
		}
	}
	if(t4n > 0x3F || t2n > 0x3F || txn > 0x3F) {
		return BP_NULL;
	}
	*pack = 0;
	if(t4n != 0) {
		pack_4 = (pack+1);
		*pack += 1;
		*pack_4++ = 0x80 | t4n;
	}
	if(t2n != 0) {
		pack_2 = (pack+1) + ((BP_NULL==pack_4)?0:(1+t4n*(4+2)));
		*pack += 1;
		*pack_2++ = 0x40 | t2n;
	}
	if(txn != 0) {
		pack_x = (pack+1) + ((BP_NULL==pack_4)?0:(1+t4n*(4+2))) + ((BP_NULL==pack_2)?0:(1+t2n*(2+2)));
		*pack += 1;
		*pack_x++ = 0xC0 | txn;
	}
	for(i = 0; i < payload->u.GETACK.SigNum; i++) {
		switch(payload->u.GETACK.SigTypeArray[i]) {
			case SIG_TYPE_U32:
				pack_4 = BP_SetBig16(pack_4, payload->u.GETACK.SigArray[i].SigId);
				pack_4 = BP_SetBig32(pack_4, payload->u.GETACK.SigArray[i].SigVal.t_u32);
				break;
			case SIG_TYPE_I32:
				pack_4 = BP_SetBig16(pack_4, payload->u.GETACK.SigArray[i].SigId);
				pack_4 = BP_SetBig32(pack_4, payload->u.GETACK.SigArray[i].SigVal.t_i32);
				break;
			case SIG_TYPE_FLT:
				pack_4 = BP_SetBig16(pack_4, payload->u.GETACK.SigArray[i].SigId);
				pack_4 = BP_SetBig32(pack_4, payload->u.GETACK.SigArray[i].SigVal.t_flt);
				break;
			case SIG_TYPE_U16:
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigId);
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigVal.t_u16);
				break;
			case SIG_TYPE_I16:
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigId);
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigVal.t_i16);
				break;
			case SIG_TYPE_ENM:
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigId);
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigVal.t_enm);
				break;
			case SIG_TYPE_STR:
				{
					BP_UINT8 n = strlen_bp(payload->u.GETACK.SigArray[i].SigVal.t_str);
					BP_UINT8 j;
					pack_x = BP_SetBig16(pack_x, payload->u.GETACK.SigArray[i].SigId);
					for(j = 0; j < n; j++) {
						*pack_x++ = payload->u.GETACK.SigArray[i].SigVal.t_str[i];
					}
				}
				break;
			case SIG_TYPE_BOOLEAN:
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigId);
				pack_2 = BP_SetBig16(pack_2, payload->u.GETACK.SigArray[i].SigVal.t_bool);
				break;
		}
	}
	(pack = pack_x) || (pack = pack_2) || (pack = pack_4);
	return pack;
}

BP_UINT8 * make_pld_postack(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	return pack;
}

BP_UINT8 * make_pld_rprt(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	BP_UINT16 i, j, k;
	BP_UINT16 t4n = 0, t2n = 0, txn = 0;
	BP_UINT16 idx_tmp;
    BP_UINT8 byte_tmp = 0;
#if CHECKSUM_TYPE == 0
	BP_UINT32 sig_map_crc;
#else
	BP_UINT16 sig_map_crc;
#endif
	const BP_UINT8 * sig_map;
	const BP_UINT8 * lang;
	BP_UINT8 * pack_4 = BP_NULL;
	BP_UINT8 * pack_2 = BP_NULL;
	BP_UINT8 * pack_x = BP_NULL;
	BP_UINT8 * pack_old = pack;
    BP_UINT8 * pack_enum_lang_num;
    BP_SigTable * sig_table_tmp;

    if(vrb_head->u.REPORT.Flags & BP_VRB_FLAG_SYS_SIG_SET_MSK) {
        /* pack system signal map */
        for(i = 0; i < g_SysSigMapSize; i++) {
			*pack++ = g_SysSigMap[i].Dist;
            memcpy_bp(pack, g_SysSigMap[i].SigMap, g_SysSigMap[i].SigMapSize);
        }
		/* TODO: pack custom system signal attribute map*/
        /* pack custom signal map */
        pack = BP_SetBig16(pack, (BP_UINT16)g_CusSigNum);
        for(i = 0; i < g_CusSigNum; i++) {
            sig_table_tmp = &sig_table_tmp;
            pack = BP_SetBig16(pack, sig_table_tmp->SigId);
            *pack++ = (sig_table_tmp->SigType << 4) | (sig_table_tmp->Perm << 3) | (sig_table_tmp->EnStatics << 2) | (sig_table_tmp->EnAlarm << 1) | (sig_table_tmp->IsDisplay);
            for(j = 7; j > 0; j--) {
                byte_tmp = STD_LANGUAGE_SUPPORTED_MASK & (0x01 << j);
                if(0 == byte_tmp) {
                    continue;
                }
                if(0 == STD_LANGUAGE_SUPPORTED_MASK & ((0x01 << (j+1)) - 1)) {
                    byte_tmp |= 0x01; // end flag
                }
                *pack++ = byte_tmp;
                /* construct signal name language */
                for(k = 0; k < g_CusSigNameLangMapNum; k++) {
                    if(g_CusSigNameLangMap[k].SigId == sig_table_tmp->SigId) {
                        if(g_CusSigNameLangMap[k].LangId == 0) {
                            continue;
                        }
                        lang = g_CusSigNameLang[((g_CusSigNameLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j];
                        byte_tmp = (BP_UINT8)strlen_bp(lang);
                        pack = BP_Set1ByteField(pack, lang, byte_tmp);
                        break;
                    }
                }

                /* construct signal unit language */
                for(k = 0; k < g_CusSigUnitLangMapNum; k++) {
                    if(g_CusSigUnitLangMap[k].SigId == sig_table_tmp->SigId) {
                        if(g_CusSigUnitLangMap[k].LangId == 0) {
                            continue;
                        }
                        lang = g_CusSigUnitLang[((g_CusSigUnitLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j];
                        byte_tmp = (BP_UINT8)strlen_bp(lang);
                        pack = BP_Set1ByteField(pack, lang, byte_tmp);
                        break;
                    }
                }

                /* construct signal group language */
                for(k = 0; k < g_CusSigGroupLangMapNum; k++) {
                    if(g_CusSigGroupLangMap[k].SigId == sig_table_tmp->SigId) {
                        if(g_CusSigGroupLangMap[k].LangId == 0) {
                            continue;
                        }
                        lang = g_CusSigGroupLang[((g_CusSigGroupLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j];
                        byte_tmp = (BP_UINT8)strlen_bp(lang);
                        pack = BP_Set1ByteField(pack, lang, byte_tmp);
                        break;
                    }
                }


                /* construct enum signal language if any*/
                if(SIG_TYPE_ENM == sig_table_tmp->SigType) {
                    pack_enum_lang_num = pack;
                    *pack_enum_lang_num = 0;

                    for(k = 0; k < g_CusSigEnumLangMapNum; k++) {
                        if(g_CusSigEnumLangMap[k].SigId == sig_table_tmp->SigId) {
                            if(g_CusSigEnumLangMap[k].LangId == 0) {
                                continue;
                            }
                            lang = g_CusSigEnumLang[((g_CusSigEnumLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j];
                            byte_tmp = (BP_UINT8)strlen_bp(lang);
                            pack = BP_Set1ByteField(pack, lang, byte_tmp);
                            *pack_enum_lang_num += 1;
                        }
                    }
                }

            }

            switch(sig_table_tmp->SigType) {
                case SIG_TYPE_U32:
                    pack = BP_SetBig32(pack, sig_table_tmp->MinVal->t_u32);
                    pack = BP_SetBig32(pack, sig_table_tmp->MaxVal->t_u32);
                    pack = BP_SetBig32(pack, sig_table_tmp->DefVal->t_u32);
                    break;
                case SIG_TYPE_U16:
                    pack = BP_SetBig16(pack, sig_table_tmp->MinVal->t_u16);
                    pack = BP_SetBig16(pack, sig_table_tmp->MaxVal->t_u16);
                    pack = BP_SetBig16(pack, sig_table_tmp->DefVal->t_u16);
                    break;
                case SIG_TYPE_I32:
                    pack = BP_SetBig32(pack, sig_table_tmp->MinVal->t_i32);
                    pack = BP_SetBig32(pack, sig_table_tmp->MaxVal->t_i32);
                    pack = BP_SetBig32(pack, sig_table_tmp->DefVal->t_i32);
                    break;
                case SIG_TYPE_I16:
                    pack = BP_SetBig16(pack, sig_table_tmp->MinVal->t_i16);
                    pack = BP_SetBig16(pack, sig_table_tmp->MaxVal->t_i16);
                    pack = BP_SetBig16(pack, sig_table_tmp->DefVal->t_i16);
                    break;
                case SIG_TYPE_ENM:
                    break;
                case SIG_TYPE_FLT:
                    *pack++ = sig_table_tmp->Accuracy;
                    pack = BP_SetBig32(pack, sig_table_tmp->MinVal->t_flt);
                    pack = BP_SetBig32(pack, sig_table_tmp->MaxVal->t_flt);
                    pack = BP_SetBig32(pack, sig_table_tmp->DefVal->t_flt);
                    break;
                case SIG_TYPE_STR:
                    byte_tmp = strlen_bp(sig_table_tmp->DefVal->t_str);
                    pack = BP_Set1ByteField(pack, sig_table_tmp->DefVal->t_str, byte_tmp);
                    break;
                case SIG_TYPE_BOOLEAN:
                    *pack++ = sig_table_tmp->DefVal->t_bool;
                    break;
            }

            if(sig_table_tmp->EnAlarm) {
                *pack++ = sig_table_tmp->AlmClass;
                *pack++ = sig_table_tmp->DelayBeforeAlm;
                *pack++ = sig_table_tmp->DelayAfterAlm;
            }

        }
#if CHECKSUM_TYPE == 0
		sig_map_crc = BP_calc_crc32(pack_old, (BP_WORD)(pack - pack_old));
		pack = BP_SetBig32(pack, sig_map_crc);
#else
		sig_map_crc = BP_calc_crc16(pack_old, (BP_WORD)(pack - pack_old));
		pack = BP_SetBig16(pack, sig_map_crc);
#endif
	} else {
		*pack++ = (BP_UINT8)(payload->u.REPORT.SysSigValEleNum + payload->u.REPORT.CusSigValEleNum);

		// BP_SigvalSort(payload->u.REPORT.CusSigArray, payload->u.REPORT.CusSigValEleNum);
		for(i = 0; i < payload->u.REPORT.CusSigValEleNum; i++) {
			pack = BP_SetBig16(pack, payload->u.REPORT.CusSigArray[i].SigId);
			pack = BP_SetSigVal2Buf(pack, &(payload->u.REPORT.CusSigArray[i]));
		}

		// BP_SigvalSort(payload->u.REPORT.SysSigArray, payload->u.REPORT.SysSigValEleNum);
		for(i = 0; i < payload->u.REPORT.SysSigValEleNum; i++) {
			pack = BP_SetBig16(pack, payload->u.REPORT.SysSigArray[i].SigId);
			pack = BP_SetSigVal2Buf(pack, &(payload->u.REPORT.SysSigArray[i]));
		}
	}
	// else {
	// 	for(i = 0; i < payload->u.REPORT.EleNum; i++) {
	// 		*pack++ = payload->u.REPORT.SysSigMap->Dist;
	// 		sig_map = payload->u.REPORT.SysSigMap->SigMap;

	// 		for(j = 0; j < payload->u.REPORT.SysSigMap->SigMapSize; j++) {
	// 			*pack++ = *sig_map++;
	// 		}
	// 	}
	// }
	return pack;
}

BP_UINT8 * make_pld_ping(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	return pack;
}


