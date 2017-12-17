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
/// @file 	bp_ping.c
/// @brief 	for BP PING functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_ping.h>
#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>

#include <stdio.h>
#include <string.h>

PackBuf * BP_PackPing()
{
	BP_WORD i;

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

	// if(BP_NULL == name) {
	// 	return BP_NULL;
	// }
	// if(BP_NULL == password) {
	// 	return BP_NULL;
	// }

	BP_InitPack(&BP_Pack_Buf, BP_PACK_TYPE_PING_MSK, BP_Buf, BP_BUF_SIZE);
	pbuf = BP_Pack_Buf.PackStart;
	pbuf_old = pbuf;

	vrb_head.u.PING.Flags = 0;
	vrb_head.u.PING.ClntId = BP_ClientId;
	BP_SeqIdPing = BP_SeqIdCommon++;
	vrb_head.u.PING.SeqId = BP_SeqIdPing;
	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_PING);

	// no payload for ping
	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_PING, &vrb_head);

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
