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
/// @file 	bp_connect.c
/// @brief 	for BP CONNECT functions source file
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
#include <bp_report.h>
#include <bp_sig_table.h>

// #include <stdio.h>
// #include <string.h>
#include <bp_strlen.h>
#include <bp_memcpy.h>

// PackBuf * BP_PackReport(BP_UINT8 * dev_name, const BP_SysSigMap * sys_sig_map, const BP_UINT16 sys_sig_map_size)
PackBuf * BP_PackReport(BP_UINT8 * dev_name, const BP_SysSigMap * sys_sig_map, const BP_SigId2Val * sig_array, const BP_UINT16 num)
{
	BP_WORD i, j;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

	if(BP_NULL == dev_name && BP_NULL == sys_sig_map && BP_NULL == sig_array) {
		return BP_NULL;
	} else if(BP_NULL != sig_array && BP_NULL != dev_name) {
		return BP_NULL;
	} else if(BP_NULL != sig_array && BP_NULL != sys_sig_map) {
		return BP_NULL;
	}

	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_REPORT_MSK, BP_Buf, BP_BUF_SIZE);
	pbuf = BP_Pack_Buf.PackStart;
	pbuf_old = pbuf;

	vrb_head.u.REPORT.Flags = 0;
	payload.u.REPORT.EleNum = 0;
	if(BP_NULL != dev_name) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_DEV_NAME_MSK;
		// strcpy(BP_DEV_NAME, dev_name);
		memcpy_bp(BP_DEV_NAME, dev_name, strlen_bp(dev_name) + 1);
		payload.u.REPORT.DevName = BP_DEV_NAME;
		payload.u.REPORT.DevNameLen = strlen_bp(dev_name);
	}
	if(BP_NULL != sys_sig_map && 0 != num) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SYS_SIG_SET_MSK;
		payload.u.REPORT.EleNum = num;
		payload.u.REPORT.SysSigMap = sys_sig_map;
	}
	if(BP_NULL != sig_array) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SIG_VAL_SET_MSK;
		payload.u.REPORT.EleNum = num;
		payload.u.REPORT.SigArray = sig_array;
		payload.u.REPORT.SigTypeArray = g_SigTypeArray;

		for(i = 0; i < num; i++) {
			for(j = 0; j < g_SysSigNum; j++) {
				if(g_SysSigTable[j].SigId == sig_array[i].SigId) {
					g_SigTypeArray[i] = g_SysSigTable[j].SigType;
					g_SigArray[i] = g_SysSigId2Val[j];
					break;
				}
			}
			// TODO: unknown signals: get_str->SigTabArray[i]
			if(g_SysSigNum == j) {
				return BP_NULL;
			}
		}
	}
	vrb_head.u.REPORT.ClntId = BP_ClientId;
	BP_SeqIdReport = BP_SeqIdCommon++;
	vrb_head.u.REPORT.SeqId = BP_SeqIdReport;

	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_REPORT);
	// printf("debug:\n");
	// for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
	// 	printf("%02x ", pbuf_old[i]);
	// }
	// printf("\n");

	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_REPORT, &vrb_head);
	// printf("debug2:\n");
	// for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
	// 	printf("%02x ", pbuf_old[i]);
	// }
	// printf("\n");

	// set remaining length and pack the packet
	rmn_len = (BP_WORD)(pbuf-pbuf_old);
	BP_Pack_Buf.RmnLen = rmn_len;
	pbuf = BP_ToPack(&BP_Pack_Buf);

	// for(i = 0; i < BP_Pack_Buf.MsgSize; i++) {
	// 	printf("%02x ", pbuf[i]);
	// }
	// printf("\n");

	return &BP_Pack_Buf;
}

// BP_INT8 BP_ParseConnack(BP_UINT8 * msg, BP_UINT16 len)
// {
// 	return 0;
// }

// BP_INT8 BP_Connect_s(BP_UINT8 * name, BP_UINT8 * password)
// {
// 	if(BP_NULL == name) {
// 		return -1;
// 	}
// 	if(BP_NULL == password) {
// 		return -2;
// 	}
// 
// 	return 0;
// }
