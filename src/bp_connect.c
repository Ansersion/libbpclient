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
/// @file 	bp_connect.c
/// @brief 	for BP CONNECT functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_connect.h>
#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>

#include <bp_strlen.h>
#include <bp_memcpy.h>

#ifdef DEBUG
#include <stdio.h>
#endif

PackBuf * BP_PackConnect(const BPContext * bp_context, BP_UINT8 * name, BP_UINT8 * password)
{
	// BP_WORD i;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

#ifdef DEBUG
        printf("start BP_PackConnect\n");
#endif
    if(BP_NULL == bp_context) {
#ifdef DEBUG
        printf("BP_NULL == bp_context\n");
#endif
        return BP_NULL;
    }
    if(BP_NULL == bp_context->packBuf) {
#ifdef DEBUG
        printf("BP_NULL == bp_context->packBuf\n");
#endif
        return BP_NULL;
    }
    if(BP_NULL == bp_context->name) {
#ifdef DEBUG
        printf("BP_NULL == bp_context->name\n");
#endif
        return BP_NULL;
    }
    if(BP_NULL == bp_context->password) {
#ifdef DEBUG
        printf("BP_NULL == bp_context->password\n");
#endif
        return BP_NULL;
    }
	if(BP_NULL == name) {
#ifdef DEBUG
        printf("BP_NULL == name\n");
#endif
		return BP_NULL;
	}
	if(BP_NULL == password) {
#ifdef DEBUG
        printf("BP_NULL == password\n");
#endif
		return BP_NULL;
	}

	// BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_CONNECT_MSK, BP_Buf, BP_BUF_SIZE);
	if(BP_NULL == BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_CONNECT_MSK, bp_context->packBuf->Buf, bp_context->packBuf->BufSize)) {
#ifdef DEBUG
        printf("BP_InitPack failed\n");
#endif
        return BP_NULL;
    }
#ifdef DEBUG
	printf("buf[0]=%x\n", bp_context->packBuf->Buf[0]);
#endif
	pbuf = bp_context->packBuf->PackStart;
	pbuf_old = pbuf;

	vrb_head.u.CONNECT.Level = BP_LEVEL;
	vrb_head.u.CONNECT.Flags = BP_VRB_FLAG_USER_NAME_MSK | BP_VRB_FLAG_PASSWORD_MSK;
	vrb_head.u.CONNECT.Flags |= BP_VRB_FLAG_CLNT_TYPE_MSK;

	// vrb_head.u.CONNECT.ClntId = BP_ClientId;
	vrb_head.u.CONNECT.AlvTime = bp_context->BPAlivePeroid;
	vrb_head.u.CONNECT.Timeout = bp_context->BPTimeout;
	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_CONNECT);

	// strcpy(BP_Name, name);
	memcpy_bp(bp_context->name, name, strlen_bp(name) + 1);
	payload.u.CONNECT.NameLen = strlen_bp(bp_context->name);
	payload.u.CONNECT.Name = bp_context->name;
	// strcpy(BP_Password, password);
	memcpy_bp(bp_context->password, password, strlen_bp(password) + 1);
	payload.u.CONNECT.PwdLen = strlen_bp(bp_context->password);
	payload.u.CONNECT.Pwd = bp_context->password;
	// payload.u.CONNECT.ClntIdLen = BP_CLIENT_ID_LEN;
	// payload.u.CONNECT.ClntId = BP_ClientId;
	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_CONNECT, &vrb_head);

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

