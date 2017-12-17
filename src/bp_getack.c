///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017 Ansersion
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
/// @file 	bp_getack.c
/// @brief 	for BP GETACK functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>
#include <bp_sys_sig.h>
#include <bp_getack.h>
#include <bp_sig_table.h>

#include <stdio.h>
#include <string.h>

BP_SigType g_SigTypeArray[MAX_GET_ACK_SIG_NUM];
BP_SigId2Val g_SigArray[MAX_GET_ACK_SIG_NUM];

// PackBuf * BP_PackGetack(BP_UINT16 seq_id, BP_UINT8 ret_code, BP_UINT16 * sig_index_array, BP_UINT16 array_num)
PackBuf * BP_PackGetack(BP_GetStr * get_str)
{
	BP_WORD i, j;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;
	BP_UINT8 ret_code = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

	if(BP_NULL == get_str) {
		return BP_NULL;
	}

	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_GETACK_MSK, BP_Buf, BP_BUF_SIZE);
	pbuf = BP_Pack_Buf.PackStart;
	pbuf_old = pbuf;

	// vrb_head.u.REPORT.Flags = 0;
	// if(BP_NULL != get_pack_info->sig_set) {
	// 	// not supported yet
	// 	vrb_head.u.GETACK.Flags |= BP_VRB_FLAG_SIG_SET_MSK;
	// 	// TODO: judge the language 
	// 	return BP_NULL;
	// }
	vrb_head.u.GETACK.Flags = 0;
	vrb_head.u.GETACK.ClntId = get_str->ClientID;
	vrb_head.u.GETACK.SeqId = get_str->SeqId;
	// TODO: judge the ret_code

	if(0 == ret_code) {
		payload.u.GETACK.SigNum = get_str->SigNum;
		for(i = 0; i < get_str->SigNum; i++) {
			for(j = 0; j < g_SysSigNum; j++) {
				if(g_SysSigTable[j].SigId == get_str->SigTabArray[i].SigId) {
					g_SigTypeArray[i] = g_SysSigTable[j].SigType;
					g_SigArray[i] = g_SysSigId2Val[j];
					break;
				}
			}
			// TODO: unknown signals: get_str->SigTabArray[i]
			if(g_SysSigNum == j) {
				vrb_head.u.GETACK.RetCode = 0x01;
				break;
			}
		}
	}

	vrb_head.u.GETACK.RetCode = ret_code;
	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_GETACK);
	printf("debug:\n");
	for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
		printf("%02x ", pbuf_old[i]);
	}
	printf("\n");

	if(0 == ret_code) {
		payload.u.GETACK.SigTypeArray = g_SigTypeArray;
		payload.u.GETACK.SigArray = g_SigArray;

		pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_GETACK, &vrb_head);
		printf("debug2:\n");
		for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
			printf("%02x ", pbuf_old[i]);
		}
		printf("\n");
	}

	// set remaining length and pack the packet
	rmn_len = (BP_WORD)(pbuf-pbuf_old);
	BP_Pack_Buf.RmnLen = rmn_len;
	pbuf = BP_ToPack(&BP_Pack_Buf);

	for(i = 0; i < BP_Pack_Buf.MsgSize; i++) {
		printf("%02x ", pbuf[i]);
	}
	printf("\n");

	return &BP_Pack_Buf;
}

