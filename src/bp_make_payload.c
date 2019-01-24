///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017-2019 Ansersion
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
#include <bp_memcpy.h>
#include <bp_sig_table_tools.h>

#if CHECKSUM_TYPE == 0
	#include <bp_crc32.h>
#else
	#include <bp_crc16.h>
#endif


// std
#ifdef DEBUG
#include <stdio.h>
#endif
// #include <string.h>
#include <bp_strlen.h>

#define MAX_GET_ACK_SIG_NUM 	64
BP_SigType g_SigTypeArray[MAX_GET_ACK_SIG_NUM];
BP_SigId2Val g_SigArray[MAX_GET_ACK_SIG_NUM];
BP_SigValArrayEntry g_SigValArray[MAX_GET_ACK_SIG_NUM];


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
			// pack = make_pld_ping(pack, payload, vrb_head);
			// No payload
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
	// BP_UINT32 i;
#ifdef DEBUG
	printf("name=%s, len=%d\n", payload->u.CONNECT.Name, payload->u.CONNECT.NameLen);
	printf("password=%s, len=%d\n", payload->u.CONNECT.Pwd, payload->u.CONNECT.PwdLen);
#endif

	pack = BP_Set2ByteField(pack, payload->u.CONNECT.Name, payload->u.CONNECT.NameLen);
	pack = BP_Set2ByteField(pack, payload->u.CONNECT.Pwd, payload->u.CONNECT.PwdLen);
    pack = BP_SetBig16(pack, payload->u.CONNECT.SysSigTableVersion);
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
	BP_UINT16 i, j, k, l;
	// BP_UINT16 t4n = 0, t2n = 0, txn = 0;
	// BP_UINT16 idx_tmp;
    BP_UINT8 byte_tmp = 0;
    BP_UINT16 u16_tmp = 0;
#if CHECKSUM_TYPE == 0
	BP_UINT32 sig_map_crc;
#else
	BP_UINT16 sig_map_crc;
#endif
	// const BP_UINT8 * sig_map;
	const BP_UINT8 * lang;
    BP_WORD len;
	// BP_UINT8 * pack_4 = BP_NULL;
	// BP_UINT8 * pack_2 = BP_NULL;
	// BP_UINT8 * pack_x = BP_NULL;
	BP_UINT8 * pack_old = pack;
    BP_UINT8 * p_pack_tmp1 = BP_NULL;
    BP_UINT8 * p_pack_tmp2 = BP_NULL;
	BP_UINT8 * p_pack_tmp3 = BP_NULL;
    BP_SigTable * sig_table_tmp;
    BP_SigType sig_type_tmp;
    BP_UINT8 alarmTriggered = 0;
    BP_SysCusEnumUnit * sys_custom_enum_unit_tmp;
    BP_EnumSignalMap * enum_signal_map_tmp;;

	if(vrb_head->u.REPORT.Flags & (BP_VRB_FLAG_SYS_SIG_SET_MSK|BP_VRB_FLAG_SYS_SIG_ATTR_CUSTOM_MSK|BP_VRB_FLAG_CUS_SIG_SET_MSK|BP_VRB_FLAG_SIG_TAB_CHK_MSK)) {
		/* pack system signal map */
		for(i = 0; i < g_SysSigMapSize; i++) {
			*pack++ = g_SysSigMap[i].Dist;
			memcpy_bp(pack, g_SysSigMap[i].SigMap, g_SysSigMap[i].SigMapSize);
			pack += g_SysSigMap[i].SigMapSize;
		}
		pack = BP_SetBig16(pack, (BP_UINT16)g_SysCustomUnitNum);
		u16_tmp = 0xFFFF;
		for(i = 0; i < g_SysCustomUnitNum; i++) {
			if(u16_tmp != g_SysCustomUnitTable[i].SigId) {
				u16_tmp = g_SysCustomUnitTable[i].SigId;
				pack = BP_SetBig16(pack, u16_tmp);
				p_pack_tmp1 = pack;
				*p_pack_tmp1 = 0;
				pack++;
				p_pack_tmp2 = pack;
				*p_pack_tmp2 = 0;
				pack++;
				sig_type_tmp = SIG_TYPE_UNKNOWN;
				p_pack_tmp3 = BP_NULL;
			}
			switch(g_SysCustomUnitTable[i].CustomType) {
				case SYS_SIG_CUSTOM_TYPE_EN_STATISTICS:
					*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
					*p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
					break;
				case SYS_SIG_CUSTOM_TYPE_ENUM_LANG:
					if(BP_NULL == p_pack_tmp3) {
						p_pack_tmp3 = pack;
						*p_pack_tmp3 = 0;
						pack++;
                        *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
					}
                    sys_custom_enum_unit_tmp = g_SysCustomUnitTable[i].CustomValue;
					*p_pack_tmp3 = sys_custom_enum_unit_tmp->Num;
                    enum_signal_map_tmp = sys_custom_enum_unit_tmp->EnumSignalMap;
                    for(j = 0; j < sys_custom_enum_unit_tmp->Num; j++) {
                        pack = BP_SetBig16(pack, enum_signal_map_tmp[j].Key);
                        pack = BP_SetBig32(pack, (BP_UINT32)(enum_signal_map_tmp[j].Val));
                    }
					break;
				case SYS_SIG_CUSTOM_TYPE_GROUP_LANG:
					*p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
					pack = BP_SetBig16(pack, *(BP_UINT16 *)(g_SysCustomUnitTable[i].CustomValue));
					break;
				case SYS_SIG_CUSTOM_TYPE_ACCURACY:
					*p_pack_tmp1 |= 0x08;
					*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
					break;
				case SYS_SIG_CUSTOM_TYPE_MIN_VAL:
					if(SIG_TYPE_UNKNOWN == sig_type_tmp) {
						for(j = 0; j < g_SysSigNum; j++) {
							if(g_SysSigTable[j].SigId == g_SysCustomUnitTable[i].SigId) {
								sig_type_tmp = g_SysSigTable[j].SigType;
								break;
							}
						}
					}
					switch(sig_type_tmp) {
						case SIG_TYPE_U32:
						case SIG_TYPE_I32: 
						case SIG_TYPE_FLT: 
							pack = BP_SetBig32(pack, *(BP_UINT32 *)(g_SysCustomUnitTable[i].CustomValue));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
						case SIG_TYPE_U16:
						case SIG_TYPE_I16: 
							pack = BP_SetBig16(pack, *(BP_UINT16 *)(g_SysCustomUnitTable[i].CustomValue));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
					}
					break;
				case SYS_SIG_CUSTOM_TYPE_MAX_VAL:
					if(SIG_TYPE_UNKNOWN == sig_type_tmp) {
						for(j = 0; j < g_SysSigNum; j++) {
							if(g_SysSigTable[j].SigId == g_SysCustomUnitTable[i].SigId) {
								sig_type_tmp = g_SysSigTable[j].SigType;
								break;
							}
						}
					}
					switch(sig_type_tmp) {
						case SIG_TYPE_U32:
						case SIG_TYPE_I32: 
						case SIG_TYPE_FLT: 
							pack = BP_SetBig32(pack, *(BP_UINT32 *)(g_SysCustomUnitTable[i].CustomValue));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
						case SIG_TYPE_U16:
						case SIG_TYPE_I16: 
							pack = BP_SetBig16(pack, *(BP_UINT16 *)(g_SysCustomUnitTable[i].CustomValue));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
					}
					break;
				case SYS_SIG_CUSTOM_TYPE_DEF_VAL:
					if(SIG_TYPE_UNKNOWN == sig_type_tmp) {
						for(j = 0; j < g_SysSigNum; j++) {
							if(g_SysSigTable[j].SigId == g_SysCustomUnitTable[i].SigId) {
								sig_type_tmp = g_SysSigTable[j].SigType;
								break;
							}
						}
					}
					switch(sig_type_tmp) {
						case SIG_TYPE_U32:
						case SIG_TYPE_I32: 
						case SIG_TYPE_FLT: 
							pack = BP_SetBig32(pack, *(BP_UINT32 *)(g_SysCustomUnitTable[i].CustomValue));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
						case SIG_TYPE_U16:
						case SIG_TYPE_I16: 
						case SIG_TYPE_ENM: 
							pack = BP_SetBig16(pack, *(BP_UINT16 *)(g_SysCustomUnitTable[i].CustomValue));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
						case SIG_TYPE_STR:
							lang = (const BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
							pack = BP_Set1ByteField(pack, lang, strlen_bp(lang));
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
						case SIG_TYPE_BOOLEAN:
							*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
                            *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
							break;
					}
					break;
				case SYS_SIG_CUSTOM_TYPE_IS_ALARM:
					*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
                    *p_pack_tmp1 |= (1 <<g_SysCustomUnitTable[i].CustomType);
					break;
				case SYS_SIG_CUSTOM_TYPE_ALM_CLASS:
					*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
                    *p_pack_tmp2 |= (1 <<(g_SysCustomUnitTable[i].CustomType - 8));
					break;
				case SYS_SIG_CUSTOM_TYPE_ALM_DLY_BEFORE:
					*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
                    *p_pack_tmp2 |= (1 <<(g_SysCustomUnitTable[i].CustomType - 8));
					break;
				case SYS_SIG_CUSTOM_TYPE_ALM_DLY_AFTER:
					*pack++ = *(BP_UINT8 *)(g_SysCustomUnitTable[i].CustomValue);
                    *p_pack_tmp2 |= (1 <<(g_SysCustomUnitTable[i].CustomType - 8));
					break;
			}
		}
#ifdef DEBUG
		printf("pack custom signal: %d\n", g_CusSigNum);
#endif
		pack = BP_SetBig16(pack, (BP_UINT16)g_CusSigNum);
		for(i = 0; i < g_CusSigNum; i++) {
			sig_table_tmp = &g_CusSigTable[i];
			pack = BP_SetBig16(pack, sig_table_tmp->SigId);
			byte_tmp = sig_table_tmp->SigType << 4;
			byte_tmp |= sig_table_tmp->Perm << 3;
			byte_tmp |= sig_table_tmp->EnStatics << 2;
			byte_tmp |= sig_table_tmp->EnAlarm << 1;
			byte_tmp |= sig_table_tmp->IsDisplay;
			*pack++ = byte_tmp;
#ifdef DEBUG
			printf("pack custom signal type: (%x, %x, %x, %x, %x)\n", sig_table_tmp->SigType, sig_table_tmp->Perm, sig_table_tmp->EnStatics, sig_table_tmp->EnAlarm, sig_table_tmp->IsDisplay);
#endif
			for(j = 7; j > 2; j--) {
				byte_tmp = STD_LANGUAGE_SUPPORTED_MASK & (0x01 << j);
#ifdef DEBUG
				printf("custom signal language flag: %x\n", byte_tmp);
#endif
				if(0 == byte_tmp) {
					continue;
				}
				if(0 == (STD_LANGUAGE_SUPPORTED_MASK & ((0x01 << j) - 1))) {
#ifdef DEBUG
					printf("set custom signal language end flag: %x\n", j);
#endif
					byte_tmp |= 0x01; // end flag
				}
				*pack++ = byte_tmp;
				/* construct signal name language */
#ifdef DEBUG
				printf("start pack custom signal name language\n");
#endif
                
				for(k = 0; k < g_CusSigNameLangMapNum; k++) {
					if(g_CusSigNameLangMap[k].SigId == sig_table_tmp->SigId) {
						if(g_CusSigNameLangMap[k].LangId == 0) {
							continue;
						}
#ifdef DEBUG
						printf("find name: %d, %d\n", g_CusSigNameLangMap[k].LangId, j);
#endif
						lang = g_CusSigNameLang[((g_CusSigNameLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j - 2];
						byte_tmp = (BP_UINT8)strlen_bp(lang);
						pack = BP_Set1ByteField(pack, lang, byte_tmp);
						break;
					}
				}

#ifdef DEBUG
				printf("start pack custom signal unit language\n");
#endif
				/* construct signal unit language */
				for(k = 0; k < g_CusSigUnitLangMapNum; k++) {
					if(g_CusSigUnitLangMap[k].SigId == sig_table_tmp->SigId) {
						if(g_CusSigUnitLangMap[k].LangId == 0) {
							continue;
						}
						lang = g_CusSigUnitLang[((g_CusSigUnitLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j - 2];
						byte_tmp = (BP_UINT8)strlen_bp(lang);
						pack = BP_Set1ByteField(pack, lang, byte_tmp);
						break;
					}
				}
				if(k == g_CusSigUnitLangMapNum) {
                    *pack++ = 0;
				}

#ifdef DEBUG
				printf("start pack custom signal group language\n");
#endif
				/* construct signal group language */
				for(k = 0; k < g_CusSigGroupLangMapNum; k++) {
					if(g_CusSigGroupLangMap[k].SigId == sig_table_tmp->SigId) {
						if(g_CusSigGroupLangMap[k].LangId == 0) {
							continue;
						}
						lang = g_CusSigGroupLang[((g_CusSigGroupLangMap[k].LangId - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j - 2];
						byte_tmp = (BP_UINT8)strlen_bp(lang);
						pack = BP_Set1ByteField(pack, lang, byte_tmp);
						break;
					}
				}
				if(k == g_CusSigGroupLangMapNum) {
                    *pack++ = 0;
				}


// #ifdef DEBUG
// 				printf("start pack custom signal enum language\n");
// #endif
				BP_LOG("start pack custom signal enum language\n");
				/* construct enum signal language if any*/
				if(SIG_TYPE_ENM == sig_table_tmp->SigType) {
					p_pack_tmp1 = pack;
					*p_pack_tmp1 = 0;
					pack++;

					for(k = 0; k < g_CusSigId2EnumSignalMapNum; k++) {
						if(g_CusSigId2EnumSigMap[k].SigId == sig_table_tmp->SigId) {
							if(BP_NULL == g_CusSigId2EnumSigMap[k].EnumSignalMap) {
								continue;
							}
							for(l = 0; l < g_CusSigId2EnumSigMap[k].EnumSignalMapNum; l++) {
								lang = g_CusSigEnumLang[((g_CusSigId2EnumSigMap[k].EnumSignalMap[l].Val - 1) * STD_LANGUAGE_SUPPORTED_NUM) + j - 2];
								pack = BP_SetBig16(pack, g_CusSigId2EnumSigMap[k].EnumSignalMap[l].Key);
								byte_tmp = (BP_UINT8)strlen_bp(lang);
								pack = BP_Set1ByteField(pack, lang, byte_tmp);
								*p_pack_tmp1 += 1;
							}
							break;
						}
					}
				}

			}

#ifdef DEBUG
			printf("start pack custom signal value info\n");
#endif
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
					pack = BP_SetBig16(pack, sig_table_tmp->DefVal->t_enm);
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
#ifdef DEBUG
				printf("start pack custom signal alarm info\n");
#endif
				*pack++ = sig_table_tmp->AlmClass;
				*pack++ = sig_table_tmp->DelayBeforeAlm;
				*pack++ = sig_table_tmp->DelayAfterAlm;
			}

		}

        len = (BP_WORD)(pack-pack_old);

		if(vrb_head->u.REPORT.Flags & BP_VRB_FLAG_SIG_TAB_CHK_MSK) {
			pack = pack_old;
        }
#if CHECKSUM_TYPE == 0
		sig_map_crc = BP_calc_crc32(pack_old, len);
		pack = BP_SetBig32(pack, sig_map_crc);
#else
		sig_map_crc = BP_calc_crc16(pack_old, len);
		pack = BP_SetBig16(pack, sig_map_crc);
#endif
	}
	if(vrb_head->u.REPORT.Flags & BP_VRB_FLAG_SIG_VAL_MSK)
	{
		*pack++ = (BP_UINT8)(payload->u.REPORT.SigValEleNum);
#ifdef DEBUG
        printf("report: signal value num=%d\n", payload->u.REPORT.SigValEleNum);
#endif

		for(i = 0; i < payload->u.REPORT.SigValEleNum; i++) {
#ifdef DEBUG
            printf("report: signal id=%x\n", payload->u.REPORT.SigArray[i].SigId);
#endif
            sig_type_tmp = SIG_TYPE_UNKNOWN;
            if(payload->u.REPORT.SigArray[i].SigId < SYSTEM_SIGNAL_ID_START) {
                for(j = 0; j < g_CusSigNum; j++) {
#ifdef DEBUG
                    printf("report: custom signal id:%x->%x\n", payload->u.REPORT.SigArray[i].SigId, g_CusSigTable[j].SigId);
#endif
                    if(payload->u.REPORT.SigArray[i].SigId == g_CusSigTable[j].SigId) {
                        sig_type_tmp = g_CusSigTable[j].SigType;
#ifdef DEBUG
                        printf("report: custom signal type=%d\n", sig_type_tmp);
#endif
                        break;
                    }
                }
            } else {
                for(j = 0; j < g_SysSigNum; j++) {
#ifdef DEBUG
                    printf("report: system signal id:%x->%x\n", payload->u.REPORT.SigArray[i].SigId, g_SysSigTable[j].SigId);
#endif
                    if(payload->u.REPORT.SigArray[i].SigId == g_SysSigTable[j].SigId) {
                        sig_type_tmp = g_SysSigTable[j].SigType;
                        break;
                    }
                }
            }
            if(SIG_TYPE_UNKNOWN == sig_type_tmp) {
                continue;
            }
#ifdef DEBUG
            printf("report: signal type=%d\n", sig_type_tmp);
#endif
			pack = BP_SetBig16(pack, payload->u.REPORT.SigArray[i].SigId);
            pack = BP_SetSigVal2Buf2(pack, sig_type_tmp, payload->u.REPORT.SigArray[i].SigVal);
		}

	}
	return pack;
}

BP_UINT8 * make_pld_ping(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
    /* no payload */
	return pack;
}


