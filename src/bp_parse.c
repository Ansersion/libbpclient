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
/// @file 	bp_parse.c
/// @brief 	packet parsing functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_parse.h>
#include <bp_fix_flags.h>
#include <bp_vrb_flags.h>
#include <bp_sig_table.h>
#include <bp_make_payload.h>
#include <bp_sig_table_tools.h>
#include <bp_server_chain.h>
#include <bp_memcpy.h>
#include <bp_spectype.h>

#ifdef CHECKSUM_CRC32
    #include <bp_crc32.h>
#else
    #include <bp_crc16.h>
#endif

// BP_INT8 BP_ParseRprtack(BP_RprtackStr * str_rprtack, BP_UINT8 * msg, BP_UINT16 len)
// {
// 	BP_UINT8 * p_msg = BP_NULL;
// 	if(BP_NULL == str_rprtack) {
// 		return -0x01;
// 	}
// 	if(BP_NULL == msg) {
// 		return -0x02;
// 	}
//     p_msg = msg + FIX_HEAD_SIZE;
// 	p_msg = BP_GetBig16(p_msg, &(str_rprtack->SeqId));
// 	str_rprtack->RetCode = *p_msg++;
// 	return 0;
// }

BP_INT8 BP_ParseRprtack(BPContext * bp_context, BP_RprtackStr * str_rprtack, BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT8 * p_msg = BP_NULL;
    if(BP_NULL == bp_context) {
        return -0x01;
    }
	if(BP_NULL == str_rprtack) {
		return -0x02;
	}
	if(BP_NULL == msg) {
		return -0x03;
	}
    p_msg = msg + FIX_HEAD_SIZE;
	str_rprtack->Flags = *p_msg++;
	p_msg = BP_GetBig16(p_msg, &(str_rprtack->SeqId));
    if(bp_context->SeqIDReport != str_rprtack->SeqId) {
        return -0x04;
    }
	str_rprtack->RetCode = *p_msg++;
    str_rprtack->SigIdErr = 0;
    if(str_rprtack->RetCode != 0) {
        p_msg = BP_GetBig16(p_msg, &(str_rprtack->SigIdErr));
    }
	return 0;
}

BP_INT8 BP_ParsePingack(BPContext * bp_context, BP_PingackStr * str_pingack, BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT8 * p_msg = BP_NULL;
	if(BP_NULL == str_pingack) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
    p_msg = msg + FIX_HEAD_SIZE;
	str_pingack->Flags = *p_msg++;
	p_msg = BP_GetBig16(p_msg, &(str_pingack->SeqId));
    if(bp_context->SeqIDPing != str_pingack->SeqId) {
        return -0x03;
    }
	str_pingack->RetCode = *p_msg++;
	return 0;
}

BP_INT8 BP_ParsePost(BP_PostStr * str_post, BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT8 * p_msg = BP_NULL;
	BP_UINT8 i = 0, j = 0, k = 0;
	BP_UINT8 sig_num = 0, sig_type = 0;
	BP_UINT8 sig_str_size = 0;
	BP_UINT8 sig_idx_tmp = 0;
	BP_UINT16 sig_id_tmp = 0;
	BP_SigId2Val * bpSigId2ValTmp = BP_NULL;
	if(BP_NULL == str_post) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
    p_msg = msg + FIX_HEAD_SIZE;
	str_post->Flags = *p_msg++;
	p_msg = BP_GetBig16(p_msg, &(str_post->SeqId));
#ifdef DEBUG
    printf("ParsePost: seqId=%d\n", str_post->SeqId);
#endif
	str_post->SigNum = 0;
    p_msg+=4; // skip the device id
	if(str_post->Flags & BP_VRB_FLAG_SIG_VAL_MSK) {
		sig_num = *p_msg++;
		for(i = 0; i < sig_num; i++) {
			p_msg = BP_GetBig16(p_msg, &sig_id_tmp);
			sig_type = *p_msg++ & 0x0F;
			sig_idx_tmp = BP_GetSigIdx(sig_id_tmp);
			if(SIG_INDEX_INVALID == sig_idx_tmp) {
				return -0x11;
			}
			if(g_SysSigTable[sig_idx_tmp].SigType != sig_type) {
				return -0x13;
			}
			g_SigValArray[i].SigId = sig_id_tmp;
			g_SigValArray[i].SigIdx = sig_idx_tmp;
			bpSigId2ValTmp = BP_GetSigId2Val(sig_idx_tmp, sig_id_tmp);
			if(BP_NULL == bpSigId2ValTmp) {
				return -0x14;
			}
			switch(g_SysSigTable[sig_idx_tmp].SigType) {
				case SIG_TYPE_U32:
					p_msg = BP_GetBig32(p_msg, (BP_UINT32 *)&(bpSigId2ValTmp->SigVal.t_u32));
					break;
				case SIG_TYPE_U16:
					p_msg = BP_GetBig16(p_msg, (BP_UINT16 *)&(bpSigId2ValTmp->SigVal.t_u16));
					break;
				case SIG_TYPE_I32:
					p_msg = BP_GetBig32(p_msg, (BP_UINT32 *)&(bpSigId2ValTmp->SigVal.t_i32));
					break;
				case SIG_TYPE_I16:
					p_msg = BP_GetBig16(p_msg, (BP_UINT16 *)&(bpSigId2ValTmp->SigVal.t_i16));
					break;
				case SIG_TYPE_ENM:
					p_msg = BP_GetBig16(p_msg, (BP_UINT16 *)&(bpSigId2ValTmp->SigVal.t_enm));
					break;
				case SIG_TYPE_FLT:
					p_msg = BP_GetBig32(p_msg, (BP_UINT32 *)&(bpSigId2ValTmp->SigVal.t_flt));
					break;
				case SIG_TYPE_STR:
					sig_str_size = *p_msg++;
					for(k = 0; k < sig_str_size; k++) {
						bpSigId2ValTmp->SigVal.t_str[k] = *p_msg++;
					}
					break;
				default:
					return -0x12;
			}
		}
		str_post->SigNum += sig_num;
		str_post->SigValArray = g_SigValArray;
	}
	return 0;
}

BP_INT8 BP_ParseGet(BP_GetStr * str_get, BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT8 * p_msg;
	BP_UINT8 i;
	if(BP_NULL == str_get) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
	//if(len < 127 + MIN_FIX_HEAD_SIZE) {
	//	p_msg = msg + MIN_FIX_HEAD_SIZE;
	//} else {
	//	p_msg = msg + MAX_FIX_HEAD_SIZE;

	//}
    p_msg = msg + FIX_HEAD_SIZE;
	str_get->Flags = *p_msg++;
	p_msg = BP_GetBig16(p_msg, &(str_get->ClientID));
	p_msg = BP_GetBig16(p_msg, &(str_get->SeqId));
	// str_get->RetCode = *p_msg++;
	
	str_get->SigNum = *p_msg++;
	for(i = 0; i < str_get->SigNum; i++) {
		p_msg = BP_GetBig16(p_msg, &(g_SigArray[i].SigId));
	}
	str_get->SigTabArray = g_SigArray;
	return 0;
}

BP_INT8 BP_ParseConnack(BPContext * bp_context, BP_ConnackStr * str_connack, BP_UINT8 * msg, BP_UINT16 len)
{
    BPServerNode bp_server_node;
    BP_WORD tmp;

    if(BP_NULL == bp_context) {
        return -0x01;
    }
	if(BP_NULL == str_connack) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
    msg += FIX_HEAD_SIZE;
	str_connack->Level = *msg++;
	str_connack->Flags = *msg++;
	msg = BP_GetBig16(msg, &(str_connack->AlvTime));
	str_connack->Timeout = *msg++;
	str_connack->RetCode = *msg++;

    msg = BP_GetBig16(msg, &(bp_context->SysSigTableVersion));
    msg = ParseServerNode(&bp_server_node, msg);
    if(BP_NULL == msg) {
        return -3;
    }

    tmp = UpdateUpperServerNode(bp_context->ServerChain, bp_context->ServerChainSize, bp_context->CurrentServerNodeIndex, &bp_server_node);

#ifdef DEBUG
    printf("GetCurSrvIndex UpdateUpperServer=%d\n", tmp);
#endif
    if(tmp >= 0) {
        bp_context->CurrentServerNodeIndex = tmp;
    }

    msg = ParseServerNode(&bp_server_node, msg);
    if(BP_NULL == msg) {
        return -4;
    }
    tmp = UpdateLowerServerNode(bp_context->ServerChain, bp_context->ServerChainSize, bp_context->CurrentServerNodeIndex, &bp_server_node);
#ifdef DEBUG
    printf("GetCurSrvIndex UpdateLowerServer=%d\n", tmp);
#endif
    if(tmp >= 0) {
        bp_context->CurrentServerNodeIndex = tmp;
    }


	return 0;
}

BP_INT8 BP_ParseSpecset(BPContext * bp_context, BP_SpecsetStr * str_specset, BP_UINT8 * msg, BP_UINT16 len)
{
    if(BP_NULL == bp_context) {
        return -0x01;
    }
	if(BP_NULL == str_specset) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
    msg += FIX_HEAD_SIZE;
	msg = BP_GetBig16(msg, &(str_specset->Type));
    switch(str_specset->Type) {
        case BP_SPECTYPE_SET_SSID_AND_ADMIN:
            str_specset->SsidLen = *msg++;
            memcpy_bp(str_specset->Ssid, msg, str_specset->SsidLen);
            msg += str_specset->SsidLen;

            str_specset->PasswordLen = *msg++;
            memcpy_bp(str_specset->Password, msg, str_specset->PasswordLen);
            msg += str_specset->PasswordLen;

            str_specset->UserNameLen = *msg++;
            memcpy_bp(str_specset->UserName, msg, str_specset->UserNameLen);
            msg += str_specset->UserNameLen;
            break;
    }

	return 0;
}

BP_INT16 BP_ParseFixHead(BP_UINT8 * msg, BP_UINT8 * type_and_flags, BP_UINT16 * rmn_len)
{
	BP_UINT8 i;
	// BP_WORD multiplier;
	if(BP_NULL == msg) {
#ifdef DEBUG
        printf("BP_NULL == msg\n");
#endif
		return -0x1;
	}
	if(BP_NULL == type_and_flags) {
#ifdef DEBUG
        printf("type_and_flags == msg\n");
#endif
		return -0x2;
	}
	if(BP_NULL == rmn_len) {
#ifdef DEBUG
        printf("rmn_len == msg\n");
#endif
		return -0x3;
	}
	i = 0;
	*type_and_flags = msg[i++];
    if(CHECKSUM_TYPE != (*type_and_flags & 0x01)) {
        return -0x4;
    }
    if(ENCRYPTION_TYPE != ((*type_and_flags >> 1) & 0x03)) {
        return -0x5;
    }

    *rmn_len = msg[i++];
    *rmn_len = (*rmn_len << 8) + msg[i++];

	return 0;
}

#ifdef CHECKSUM_CRC32
BP_INT8 BP_CheckCRC32(BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT32 crc;
	if(BP_NULL == msg) {
		return -0x01;
	}
	if(len < 4) {
		return -0x02;
	}
	BP_GetNet32(msg + len - 4, &crc);

	if(BP_calc_crc32(msg, len - 4) != crc) {
		return -0x11;
	}

	return 0;
}

#else

BP_INT8 BP_CheckCRC16(BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT16 crc;
	if(BP_NULL == msg) {
		return -0x01;
	}
	if(len < 2) {
		return -0x02;
	}
	BP_GetNet16(msg + len - 2, &crc);

	if(BP_calc_crc16(msg, len - 2) != crc) {
		return -0x11;
	}

	return 0;
}
#endif

BP_INT8 BP_CheckCRC(BP_UINT8 crc_flags, BP_UINT8 * msg, BP_UINT16 len)
{
	// if(crc_flags & BP_FIX_FLAG_CRC16_MSK) {
	// 	return BP_CheckCRC16(msg, len);
	// } else {
	// 	return BP_CheckCRC32(msg, len);
	// }
#ifdef CHECKSUM_CRC32
	return BP_CheckCRC32(msg, len);
#else 
	return BP_CheckCRC16(msg, len);
#endif
}

BP_UINT8 * ParseServerNode(BPServerNode * server_node, BP_UINT8 * msg) 
{
    if(BP_NULL == server_node || BP_NULL == msg) {
        return msg;
    }
    server_node->Type = *msg++;
    switch(server_node->Type) {
        case BP_SERVER_TYPE_IPV4: 
            {
                memcpy_bp(server_node->Address, msg, 4);
                msg += 4;
                break;
            }
        case BP_SERVER_TYPE_IPV6: 
            {
                memcpy_bp(server_node->Address, msg, 16);
                msg += 16;
                break;
            }
        case BP_SERVER_TYPE_DOMAIN:
            {
                BP_UINT8 len = *msg++;
                if(len > BP_SERVER_ADDRESS_SIZE - 1) {
                    // NOTE: domain is too long
                    return BP_NULL;
                }
                memcpy_bp(server_node->Address, msg, len);
                server_node->Address[len] = '\0';
                msg += len;
                break;
            }
        default:
            {
                /* default server node */
            }
    }

    return msg;
}
