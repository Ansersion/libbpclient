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
/// @file 	bp_disconn.c
/// @brief 	for BP DISCONN functions source file
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

PackBuf * BP_PackDisconn()
{
	BP_WORD i;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_DISCONN_MSK, BP_Buf, BP_BUF_SIZE);
	pbuf = BP_Pack_Buf.PackStart;
	pbuf_old = pbuf;

	// variable header
	vrb_head.u.DISCONN.ClntId = BP_ClientId;
	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_DISCONN);

	// payload
	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_DISCONN, &vrb_head);

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
