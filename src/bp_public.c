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
	if(BP_NULL == pack || BP_NULL == field_len) {
		return BP_NULL;
	}
	p_pack = BP_SetBig16(p_pack, field_len);
	memcpy_bp(p_pack, field, field_len);

	return p_pack+field_len;
}
