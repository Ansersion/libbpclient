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
/// @file 	bp_make_pack.c
/// @brief 	APIs to make BP packet
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_make_pack.h>
#include <bp_memset.h>
#include <bp_crc32.h>

PackBuf * BP_InitPack(PackBuf * pack_buf, BP_UINT8 type_msk, BP_UINT8 * buf, BP_WORD size)
{
	if(BP_NULL == pack_buf) {
		return BP_NULL;
	}
	if(BP_NULL == buf) {
		return BP_NULL;
	}
	if(size < 4) {
		return BP_NULL;
	}
	// pack_buf->FxHdType = type_msk;
	// pack_buf->FxHdType = type_msk;
	// pack_buf->FxHdType = type_msk;
	// pack_buf->FxHdRmnLen[0] = 0;
	// pack_buf->FxHdRmnLen[1] = 0;
	pack_buf->RmnLen = 0;
	pack_buf->MsgSize = 0;
	pack_buf->BufSize = size;
	memset_bp(buf, 0, size);
	pack_buf->Buf = buf;
	pack_buf->Buf[0] = type_msk;
	pack_buf->PackStart = &(pack_buf->Buf[3]); // "3" is the max size of fixed header
	return pack_buf;
}

#ifdef BP_MEM_MNG
PackBuf * BP_InitPack2(PackBuf * pack_buf, BP_WORD size)
{
	return BP_NULL;
}
#endif

BP_UINT8 * BP_ToPack(PackBuf * pack_buf)
{
#define SIZE_OF_CRC32 4
	BP_WORD rmn_len = 0;
	BP_WORD i = 0;
	BP_UINT8 * pack_start = BP_NULL;
	BP_UINT32 crc = 0;
	if(BP_NULL == pack_buf) {
		return BP_NULL;
	}
	pack_buf->RmnLen += SIZE_OF_CRC32; // "4" is the size of CRC32
	pack_buf->MsgSize = 0;
	rmn_len = pack_buf->RmnLen;

	if(rmn_len < 128) {
		pack_buf->Buf[1] = pack_buf->Buf[0];
		pack_buf->Buf[2] = (BP_UINT8)(rmn_len);
		pack_start = &(pack_buf->Buf[1]);
		pack_buf->MsgSize = 2 + pack_buf->RmnLen;
	} else {
		i = 1;
		do {
			if(3 == i) {
				// too big remaining length
				return BP_NULL;
			}
			pack_buf->Buf[i] = rmn_len % 128;
			rmn_len = rmn_len / 128;
			if(rmn_len > 0) {
				pack_buf->Buf[i] |= 128;
			}
			i++;
		} while(rmn_len > 0);
		pack_start = pack_buf->Buf;
		pack_buf->MsgSize = 3 + pack_buf->RmnLen;
	}
	pack_buf->PackStart = pack_start;
	crc = BP_calc_crc32(pack_start, pack_buf->MsgSize - SIZE_OF_CRC32);
	BP_SetBig32(pack_start + pack_buf->MsgSize - SIZE_OF_CRC32, crc);

	return pack_buf->PackStart;
}

PackBuf * BP_ReinitPack(PackBuf * pack_buf, BP_UINT8 type_msk)
{
	if(BP_NULL == pack_buf) {
		return BP_NULL;
	}
	if(BP_NULL == pack_buf->Buf) {
		return BP_NULL;
	}
	pack_buf->RmnLen = 0;
	pack_buf->MsgSize = 0;
	memset_bp(pack_buf->Buf, 0, pack_buf->BufSize);
	pack_buf->Buf[0] = type_msk;
	pack_buf->PackStart = &(pack_buf->Buf[3]); // "3" is the max size of fixed header
	return pack_buf;
}
