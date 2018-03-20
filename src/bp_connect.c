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

#include <bp_connect.h>
#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>

// #include <stdio.h>
// #include <string.h>
#include <bp_strlen.h>
#include <bp_memcpy.h>

PackBuf * BP_PackConnect(BP_UINT8 * name, BP_UINT8 * password)
{
	BP_WORD i;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

	if(BP_NULL == name) {
		return BP_NULL;
	}
	if(BP_NULL == password) {
		return BP_NULL;
	}

	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_CONNECT_MSK, BP_Buf, BP_BUF_SIZE);
	pbuf = BP_Pack_Buf.PackStart;
	pbuf_old = pbuf;

	vrb_head.u.CONNECT.Level = BP_LEVEL;
	vrb_head.u.CONNECT.Flags = BP_VRB_FLAG_USER_NAME_MSK | BP_VRB_FLAG_PASSWORD_MSK;
	if(0 == BP_ClientType) {
		vrb_head.u.CONNECT.Flags |= BP_VRB_FLAG_DEV_CLNT_MSK;
	} else if(1 == BP_ClientType) {
		vrb_head.u.CONNECT.Flags |= BP_VRB_FLAG_USER_CLNT_MSK;
	}

	vrb_head.u.CONNECT.ClntId = BP_ClientId;
	vrb_head.u.CONNECT.AlvTime = BP_AliveTime;
	vrb_head.u.CONNECT.Timeout = BP_Timeout;
	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_CONNECT);

	// strcpy(BP_Name, name);
	memcpy_bp(BP_Name, name, strlen_bp(name) + 1);
	payload.u.CONNECT.NameLen = strlen_bp(BP_Name);
	payload.u.CONNECT.Name = BP_Name;
	// strcpy(BP_Password, password);
	memcpy_bp(BP_Password, password, strlen_bp(password) + 1);
	payload.u.CONNECT.PwdLen = strlen_bp(BP_Password);
	payload.u.CONNECT.Pwd = BP_Password;
	payload.u.CONNECT.ClntIdLen = BP_CLIENT_ID_LEN;
	payload.u.CONNECT.ClntId = BP_ClientId;
	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_CONNECT, &vrb_head);

	// set remaining length and pack the packet
	rmn_len = (BP_WORD)(pbuf-pbuf_old);
	BP_Pack_Buf.RmnLen = rmn_len;
	pbuf = BP_ToPack(&BP_Pack_Buf);

// 	for(i = 0; i < BP_Pack_Buf.MsgSize; i++) {
// 		printf("%02x ", pbuf[i]);
// 	}
// 	printf("\n");
// 
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
