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

#include <stdio.h>
#include <string.h>

PackBuf * BP_PackReport(BP_UINT8 * dev_name, const BP_SysSigMap * sys_sig_map)
{
	BP_WORD i;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

	if(BP_NULL == dev_name && BP_NULL == sys_sig_map) {
		return BP_NULL;
	}

	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_REPORT_MSK, BP_Buf, BP_BUF_SIZE);
	pbuf = BP_Pack_Buf.PackStart;
	pbuf_old = pbuf;

	vrb_head.u.REPORT.Flags = 0;
	if(BP_NULL != dev_name) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_DEV_NAME_MSK;
	}
	if(BP_NULL != sys_sig_map) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SYS_SIG_SET_MSK;
	}
	vrb_head.u.REPORT.ClntId = BP_ClientId;
	BP_SeqIdReport = BP_SeqIdCommon++;
	vrb_head.u.REPORT.SeqID = BP_SeqIdReport;

	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_REPORT);
	printf("debug:\n");
	for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
		printf("%02x ", pbuf_old[i]);
	}
	printf("\n");

	payload.u.REPORT.SysSigMapSize = g_SysSigMapSize;
	payload.u.REPORT.SysSigMap = sys_sig_map;
	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_REPORT);
	printf("debug2:\n");
	for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
		printf("%02x ", pbuf_old[i]);
	}
	printf("\n");

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
