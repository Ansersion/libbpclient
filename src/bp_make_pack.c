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
	if(size < FIX_HEAD_SIZE + CHECKSUM_SIZE) {
		return BP_NULL;
	}
#ifdef DEBUG
        printf("start BP_InitPack\n");
#endif
	pack_buf->RmnLen = 0;
	pack_buf->MsgSize = 0;
	pack_buf->BufSize = size;
	/* Note: not initialize buffer to accelerate processing */
	/* memset_bp(buf, 0, size); */
	pack_buf->Buf = buf;
	pack_buf->Buf[0] = type_msk;
	pack_buf->PackStart = &(pack_buf->Buf[FIX_HEAD_SIZE]);
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
	BP_WORD i = 0;
	BP_UINT8 * pack_start = BP_NULL;
	BP_UINT32 crc = 0;
	if(BP_NULL == pack_buf) {
		return BP_NULL;
	}
	pack_buf->RmnLen += CHECKSUM_SIZE;
	pack_buf->Buf[1] = (pack_buf->RmnLen >> 8)& 0xFF;
	pack_buf->Buf[2] = pack_buf->RmnLen & 0xFF;

	pack_buf->MsgSize = FIX_HEAD_SIZE + pack_buf->RmnLen;

	// printf("buf[0]=%x\n", pack_buf->Buf[0]);
	pack_buf->PackStart = pack_buf->Buf;
	crc = BP_calc_crc32(pack_buf->PackStart, pack_buf->MsgSize - CHECKSUM_SIZE);
	BP_SetBig32(pack_buf->PackStart + pack_buf->MsgSize - CHECKSUM_SIZE, crc);

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
