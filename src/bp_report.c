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
/// @file 	bp_report.c
/// @brief 	for BP REPORT functions source file
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
#include <bp_sig_table_tools.h>
#include <bp_report.h>
#include <bp_sig_table.h>
#include <bp_custom_sig_table.h>

#include <bp_strlen.h>
#include <bp_memcpy.h>

PackBuf * BP_PackReport(const BP_SigId2Val * sig_array, const BP_UINT16 num)
{
	// BP_WORD i, j;

	// BP_UINT8 * pbuf, * pbuf_old;
	// BP_WORD rmn_len = 0;

	// BPPackVrbHead vrb_head;
	// BPPackPayload payload;

	// if(BP_NULL == sys_sig_map && BP_NULL == sig_array) {
	// 	return BP_NULL;
	// } else if(BP_NULL != sig_array && BP_NULL != dev_name) {
	// 	return BP_NULL;
	// } else if(BP_NULL != sig_array && BP_NULL != sys_sig_map) {
	// 	return BP_NULL;
	// }

	// BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_REPORT_MSK, BP_Buf, BP_BUF_SIZE);
	// pbuf = BP_Pack_Buf.PackStart;
	// pbuf_old = pbuf;

	// vrb_head.u.REPORT.Flags = 0;
	// payload.u.REPORT.EleNum = 0;
	// if(BP_NULL != dev_name) {
	// 	vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_DEV_NAME_MSK;
	// 	// strcpy(BP_DEV_NAME, dev_name);
	// 	memcpy_bp(BP_DEV_NAME, dev_name, strlen_bp(dev_name) + 1);
	// 	payload.u.REPORT.DevName = BP_DEV_NAME;
	// 	payload.u.REPORT.DevNameLen = strlen_bp(dev_name);
	// }
	// if(BP_NULL != sys_sig_map && 0 != num) {
	// 	vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SYS_SIG_SET_MSK;
	// 	payload.u.REPORT.EleNum = num;
	// 	payload.u.REPORT.SysSigMap = sys_sig_map;
	// }
	// if(BP_NULL != sig_array) {
	// 	vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SIG_VAL_SET_MSK;
	// 	payload.u.REPORT.EleNum = num;
	// 	payload.u.REPORT.SigArray = sig_array;
	// 	payload.u.REPORT.SigTypeArray = g_SigTypeArray;

	// 	for(i = 0; i < num; i++) {
	// 		for(j = 0; j < g_SysSigNum; j++) {
	// 			if(g_SysSigTable[j].SigId == sig_array[i].SigId) {
	// 				g_SigTypeArray[i] = g_SysSigTable[j].SigType;
	// 				g_SigArray[i] = g_SysSigId2Val[j];
	// 				break;
	// 			}
	// 		}
	// 		// TODO: unknown signals: get_str->SigTabArray[i]
	// 		if(g_SysSigNum == j) {
	// 			return BP_NULL;
	// 		}
	// 	}
	// }
	// vrb_head.u.REPORT.ClntId = BP_ClientId;
	// BP_SeqIdReport = BP_SeqIdCommon++;
	// vrb_head.u.REPORT.SeqId = BP_SeqIdReport;

	// pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_REPORT);
	// // printf("debug:\n");
	// // for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
	// // 	printf("%02x ", pbuf_old[i]);
	// // }
	// // printf("\n");

	// pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_REPORT, &vrb_head);
	// // printf("debug2:\n");
	// // for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
	// // 	printf("%02x ", pbuf_old[i]);
	// // }
	// // printf("\n");

	// // set remaining length and pack the packet
	// rmn_len = (BP_WORD)(pbuf-pbuf_old);
	// BP_Pack_Buf.RmnLen = rmn_len;
	// pbuf = BP_ToPack(&BP_Pack_Buf);

	// // for(i = 0; i < BP_Pack_Buf.MsgSize; i++) {
	// // 	printf("%02x ", pbuf[i]);
	// // }
	// // printf("\n");

	// return &BP_Pack_Buf;
	return BP_NULL;
}

PackBuf * BP_PackReportSigTabChksum(const BPContext * bp_context)
{
	BP_WORD i, j;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

    if(BP_NULL == bp_context) {
        return BP_NULL;
    }
    if(BP_NULL == bp_context->packBuf) {
        return BP_NULL;
    }

	BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_REPORT_MSK, bp_context->packBuf->Buf, BP_BUF_SIZE);
	pbuf = bp_context->packBuf->PackStart;
	pbuf_old = pbuf;

	vrb_head.u.REPORT.Flags = 0;
	vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SIG_TAB_CHK_MSK;

	payload.u.REPORT.SigTabChkCrc = BP_GetSigTabChk();

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
	bp_context->packBuf->RmnLen = rmn_len;
	pbuf = BP_ToPack(bp_context->packBuf);

	// for(i = 0; i < BP_Pack_Buf.MsgSize; i++) {
	// 	printf("%02x ", pbuf[i]);
	// }
	// printf("\n");

	return bp_context->packBuf;
}

PackBuf * BP_PackReportSigTable(const BPContext * bp_context)
{
    BP_WORD i, j;

    BP_UINT8 * pbuf, * pbuf_old;
    BP_WORD rmn_len = 0;

    BPPackVrbHead vrb_head;
    BPPackPayload payload;

    if(BP_NULL == bp_context) {
        return BP_NULL;
    }
    if(BP_NULL == bp_context->packBuf) {
        return BP_NULL;
    }

    if(BP_NULL == BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_REPORT_MSK, bp_context->packBuf->Buf, bp_context->packBuf->BufSize)) {
        return BP_NULL;
    }
#ifdef DEBUG
	printf("buf[0]=%x\n", bp_context->packBuf->Buf[0]);
#endif
    pbuf = bp_context->packBuf->PackStart;
    pbuf_old = pbuf;

    BP_SeqIdReport = BP_SeqIdCommon++;
    vrb_head.u.REPORT.SeqId = BP_SeqIdReport;
    vrb_head.u.REPORT.Flags = 0;

    // if(BP_NULL != g_SysSigTable && 0 != g_SysSigNum) {
    vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SYS_SIG_SET_MSK;
    //payload.u.REPORT.SysSigMapEleNum = g_SysSigTable;
    //payload.u.REPORT.SysSigMap = g_SysSigNum;
    // }
    // if(BP_NULL != g_CusSigTable && 0 != g_CusSigNum) {
    // vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_CUS_SIG_SET_MSK;
    // }
    // if(BP_NULL != sig_array) {
    // 	vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SIG_VAL_SET_MSK;
    // 	payload.u.REPORT.EleNum = num;
    // 	payload.u.REPORT.SigArray = sig_array;
    // 	payload.u.REPORT.SigTypeArray = g_SigTypeArray;

    // 	for(i = 0; i < num; i++) {
    // 		for(j = 0; j < g_SysSigNum; j++) {
    // 			if(g_SysSigTable[j].SigId == sig_array[i].SigId) {
    // 				g_SigTypeArray[i] = g_SysSigTable[j].SigType;
    // 				g_SigArray[i] = g_SysSigId2Val[j];
    // 				break;
    // 			}
    // 		}
    // 		// TODO: unknown signals: get_str->SigTabArray[i]
    // 		if(g_SysSigNum == j) {
    // 			return BP_NULL;
    // 		}
    // 	}
    // }
#ifdef DEBUG
	printf("start BP_make_vrb_head\n");
#endif
    pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_REPORT);

#ifdef DEBUG
	printf("start BP_make_payload\n");
#endif
    pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_REPORT, &vrb_head);

    // set remaining length and pack the packet
    rmn_len = (BP_WORD)(pbuf-pbuf_old);
    bp_context->packBuf->RmnLen = rmn_len;
    pbuf = BP_ToPack(bp_context->packBuf);

#ifdef DEBUG
	for(i = 0; i < bp_context->packBuf->MsgSize; i++) {
		printf("%02x ", pbuf[i]);
	}
	printf("\n%d\n", i);
#endif

    return bp_context->packBuf;
}

PackBuf * BP_PackReportSigVal(const BPContext *bp_context, const BP_SigId2Val * sys_sig_array, const BP_UINT16 sys_sig_num, const BP_SigId2Val * cus_sig_array, const BP_UINT16 cus_sig_num)
{
	BP_WORD i, j;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

    if(BP_NULL == bp_context) {
        return BP_NULL;
    }
    if(BP_NULL == bp_context->packBuf) {
        return BP_NULL;
    }

	if(BP_NULL == sys_sig_array && BP_NULL == cus_sig_array) {
		return BP_NULL;
	} 
	if(BP_NULL != sys_sig_array && 0 == sys_sig_num) {
		return BP_NULL;
	}
	if(BP_NULL != cus_sig_array && 0 == cus_sig_num) {
		return BP_NULL;
	}

	BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_REPORT_MSK, bp_context->packBuf->Buf, BP_BUF_SIZE);
	pbuf = bp_context->packBuf->PackStart;
	pbuf_old = pbuf;
	vrb_head.u.REPORT.Flags = 0;

	payload.u.REPORT.SysSigValEleNum = 0;
	payload.u.REPORT.SysSigArray = BP_NULL;
	if(BP_NULL != sys_sig_array) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SIG_VAL_MSK;
		payload.u.REPORT.SysSigValEleNum = sys_sig_num;
		payload.u.REPORT.SysSigArray =sys_sig_array;
	} 

	payload.u.REPORT.CusSigValEleNum = 0;
	payload.u.REPORT.CusSigArray = BP_NULL;
	if(BP_NULL != cus_sig_array) {
		vrb_head.u.REPORT.Flags |= BP_VRB_FLAG_SIG_VAL_MSK;
		payload.u.REPORT.CusSigValEleNum = cus_sig_num;
		payload.u.REPORT.CusSigArray = cus_sig_array;
	}

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

	bp_context->packBuf->RmnLen = rmn_len;
	pbuf = BP_ToPack(bp_context->packBuf);

#ifdef DEBUG
	printf("REPORT: ");
	for(i = 0; i < bp_context->packBuf->MsgSize; i++) {
		printf("%02x ", pbuf[i]);
	}
	printf("\n");
#endif

	return bp_context->packBuf;
}
