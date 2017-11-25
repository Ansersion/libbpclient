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
/// @file 	bp_public.c
/// @brief 	public tool functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_public.h>
#include <bp_memcpy.h>

BP_UINT8 BP_Buf[BP_BUF_SIZE];
BP_UINT8 BP_Name[BP_NAME_SIZE];
BP_UINT8 BP_Password[BP_PASSWORD_SIZE];
PackBuf BP_Pack_Buf;
BP_UINT8 BP_DEV_NAME[BP_NAME_SIZE];

// 0-CRC32, 1-CRC16; default 0
BP_UINT8 BP_CrcType = 0;
// 0-device client, 1-user client; default 0
BP_UINT8 BP_ClientType = 0;
// 0-no encryption, 1, 2, 3; default 0
BP_UINT8 BP_CipherType = 0;
// ; default 60
BP_UINT16 BP_AliveTime = 60;
// ; default 5
BP_UINT8 BP_Timeout = 5;
// ; default 0
BP_UINT16 BP_ClientId = BP_CLIENT_ID_APPLY;
// ; default 0
BP_UINT16 BP_SysSigSetVersion = 0;
// ; default 0
BP_UINT16 BP_SeqIdCommon = 0;
BP_UINT16 BP_SeqIdGet = 0;
BP_UINT16 BP_SeqIdPost = 0;
BP_UINT16 BP_SeqIdReport = 0;
BP_UINT16 BP_SeqIdPing = 0;

BP_UINT8 * BP_SetNet16(BP_UINT8 * dst, BP_UINT16 val)
{
	if(BP_NULL == dst) {
		return BP_NULL;
	}

	*dst++ = (BP_UINT8)((val >> 8) & (0x00FF));
	*dst++ = (BP_UINT8)(val & 0x00FF);

	return dst;
}

BP_UINT8 * BP_SetNet32(BP_UINT8 * dst, BP_UINT32 val)
{
	if(BP_NULL == dst) {
		return BP_NULL;
	}

	*dst++ = (BP_UINT8)((val >> 24) & (0x000000FF));
	*dst++ = (BP_UINT8)((val >> 16) & (0x000000FF));
	*dst++ = (BP_UINT8)((val >> 8) & (0x000000FF));
	*dst++ = (BP_UINT8)(val & 0x000000FF);

	return dst;
}

BP_UINT8 * BP_Set2ByteField(BP_UINT8 * pack, BP_UINT8 * field, BP_UINT16 field_len)
{
	BP_UINT8 * p_pack = pack;
	if(BP_NULL == pack) {
		return BP_NULL;
	}
	if(0 == field_len) {
		return BP_NULL;
	}
	p_pack = BP_SetBig16(p_pack, field_len);
	memcpy_bp(p_pack, field, field_len);

	return p_pack+field_len;
}

BP_UINT8 * BP_GetNet16(BP_UINT8 * src, BP_UINT16 * val)
{
	if(BP_NULL == src) {
		return BP_NULL;
	}
	if(BP_NULL == val) {
		return BP_NULL;
	}
	*val = *src++;
	*val = ((*val & 0x00FF) << 8) | (0xFF & (*src++));

	return src;
}

BP_UINT8 * BP_GetNet32(BP_UINT8 * src, BP_UINT32 * val)
{
	if(BP_NULL == src) {
		return BP_NULL;
	}
	if(BP_NULL == val) {
		return BP_NULL;
	}
	*val = *src++;
	*val = ((*val & 0x000000FF) << 8) | (0x000000FF & (*src++));
	*val = ((*val & 0x0000FFFF) << 8) | (0x000000FF & (*src++));
	*val = ((*val & 0x00FFFFFF) << 8) | (0x000000FF & (*src++));

	return src;

}

BP_UINT8 * BP_Get2ByteField(BP_UINT8 * pack, BP_UINT8 * field_buf, BP_UINT16 * field_len)
{
	BP_UINT8 * p_pack = pack;
	if(BP_NULL == pack) {
		return BP_NULL;
	}
	if(BP_NULL == field_buf) {
		return BP_NULL;
	}
	if(BP_NULL == field_len) {
		return BP_NULL;
	}
	p_pack = BP_GetBig16(p_pack, field_len);
	memcpy_bp(field_buf, p_pack, *field_len);

	return p_pack+(*field_len);
}
