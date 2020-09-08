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
/// @file 	bp_post.c
/// @brief 	for BP POST functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_post.h>
#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>

// #include <stdio.h>
// #include <string.h>

// PackBuf * BP_PackPost()
// {
// 	BP_WORD i;
// 
// 	BP_UINT8 * pbuf, * pbuf_old;
// 	BP_WORD rmn_len = 0;
// 
// 	BPPackVrbHead vrb_head;
// 	BPPackPayload payload;
// 
// 	// if(BP_NULL == name) {
// 	// 	return BP_NULL;
// 	// }
// 	// if(BP_NULL == password) {
// 	// 	return BP_NULL;
// 	// }
// 
// 	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_CONNECT_MSK, BP_Buf, BP_BUF_SIZE);
// 	pbuf = BP_Pack_Buf.PackStart;
// 	pbuf_old = pbuf;
// 
// 	vrb_head.u.CONNECT.Level = BP_LEVEL;
// 	vrb_head.u.CONNECT.Flags = BP_VRB_FLAG_USER_NAME_MSK | BP_VRB_FLAG_PASSWORD_MSK;
// 	if(0 == BP_ClientType) {
// 		vrb_head.u.CONNECT.Flags |= BP_VRB_FLAG_DEV_CLNT_MSK;
// 	} else if(1 == BP_ClientType) {
// 		vrb_head.u.CONNECT.Flags |= BP_VRB_FLAG_USER_CLNT_MSK;
// 	}
// 	vrb_head.u.CONNECT.ClntId = BP_ClientId;
// 	vrb_head.u.CONNECT.AlvTime = BP_AliveTime;
// 	vrb_head.u.CONNECT.Timeout = BP_Timeout;
// 	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_CONNECT);
// 
// 	strcpy(BP_Name, name);
// 	payload.u.CONNECT.NameLen = strlen(BP_Name);
// 	payload.u.CONNECT.Name = BP_Name;
// 	strcpy(BP_Password, password);
// 	payload.u.CONNECT.PwdLen = strlen(BP_Password);
// 	payload.u.CONNECT.Pwd = BP_Password;
// 	payload.u.CONNECT.ClntIdLen = BP_CLIENT_ID_LEN;
// 	payload.u.CONNECT.ClntId = BP_ClientId;
// 	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_CONNECT, &vrb_head);
// 
// 	// set remaining length and pack the packet
// 	rmn_len = (BP_WORD)(pbuf-pbuf_old);
// 	BP_Pack_Buf.RmnLen = rmn_len;
// 	pbuf = BP_ToPack(&BP_Pack_Buf);
// 
// // 	for(i = 0; i < BP_Pack_Buf.MsgSize; i++) {
// // 		printf("%02x ", pbuf[i]);
// // 	}
// // 	printf("\n");
// // 
// 	return &BP_Pack_Buf;
// }

PackBuf * BP_PackPost1SigVal(BPContext *bp_context, const BP_SigType * sig_type, const BP_SigId2Val * sig_id_2_val)
{
#ifdef DEBUG
    BP_WORD i, j;
#endif

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

    if(BP_NULL == sig_id_2_val) {
        return bp_context->packBuf;
    }

    if(BP_NULL == BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_POST_MSK)) {
#ifdef DEBUG
        printf("BP_InitPack failed\n");
#endif
        return BP_NULL;
    }
    pbuf = bp_context->packBuf->PackStart;
    pbuf_old = pbuf;
    vrb_head.u.POST.Flags = 0;
    vrb_head.u.POST.Flags |= BP_VRB_FLAG_SIG_VAL_MSK;
    // vrb_head.u.POST.SeqId = (bp_context->SeqIDComm)++;
    SET_PACK_SEQ(vrb_head.u.POST.SeqId, bp_context->SeqIDComm);
#ifdef DEBUG
    printf("post: make vrb header\n");
#endif
    pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_POST);

    payload.u.POST.DevId = bp_context->devId;
    payload.u.POST.SigNum = 1;
    payload.u.POST.SigTypeArray = sig_type;
    payload.u.POST.SigArray = sig_id_2_val;

#ifdef DEBUG
    printf("post: make payload\n");
#endif
    pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_POST, &vrb_head);
#ifdef DEBUG
    printf("debug2:\n");
    for(i = 0; i < (BP_WORD)(pbuf-pbuf_old); i++) {
    	printf("%02x ", pbuf_old[i]);
    }
    printf("\n");
#endif

    // set remaining length and pack the packet
    rmn_len = (BP_WORD)(pbuf-pbuf_old);
    bp_context->packBuf->RmnLen = rmn_len;
    pbuf = BP_ToPack(bp_context->packBuf);

#ifdef DEBUG
    printf("POST: ");
    for(i = 0; i < bp_context->packBuf->MsgSize; i++) {
        printf("%02x ", pbuf[i]);
    }
    printf("\n");
#endif

    return bp_context->packBuf;
}
