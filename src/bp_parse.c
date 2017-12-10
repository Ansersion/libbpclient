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
/// @file 	bp_parse.c
/// @brief 	packet parsing functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_parse.h>
#include <bp_crc32.h>
#include <bp_crc16.h>
#include <bp_fix_flags.h>

#include <bp_getack.h>

BP_INT8 BP_ParseGet(BP_GetStr * str_get, BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT8 * p_msg;
	BP_UINT8 i;
	if(BP_NULL == str_get) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
	if(len < 127 + MIN_FIX_HEAD_SIZE) {
		p_msg = msg + MIN_FIX_HEAD_SIZE;
	} else {
		p_msg = msg + MAX_FIX_HEAD_SIZE;

	}
	str_get->Flags = *p_msg++;
	p_msg = BP_GetBig16(p_msg, &(str_get->ClientID));
	p_msg = BP_GetBig16(p_msg, &(str_get->SeqId));
	// str_get->RetCode = *p_msg++;
	
	str_get->SigNum = *p_msg++;
	for(i = 0; i < str_get->SigNum; i++) {
		p_msg = BP_GetBig16(p_msg, &(g_SigArray[i].SigId));
	}
	str_get->SigTabArray = g_SigArray;
	return 0;
}

BP_INT8 BP_ParseConnack(BP_ConnackStr * str_connack, BP_UINT8 * msg, BP_UINT16 len)
{
	if(BP_NULL == str_connack) {
		return -0x01;
	}
	if(BP_NULL == msg) {
		return -0x02;
	}
	if(len < 127 + MIN_FIX_HEAD_SIZE) {
		str_connack->RetCode = msg[MIN_FIX_HEAD_SIZE+2];
		if(msg[MIN_FIX_HEAD_SIZE + 2] != 0) {
			return -0x11;
		}
		BP_GetBig16(msg + MIN_FIX_HEAD_SIZE + 3 + 1, &(str_connack->ClientID));
		BP_GetBig16(msg + MIN_FIX_HEAD_SIZE + 3 + 1 + 2, &(str_connack->SysSigSetVersion));
		BP_ClientId = str_connack->ClientID;
	} else {
		str_connack->RetCode = msg[MAX_FIX_HEAD_SIZE+2];
		if(msg[3 + 2] != 0) {
			return -0x11;
		}
		BP_GetBig16(msg + MAX_FIX_HEAD_SIZE + 3 + 1, &(str_connack->ClientID));
		BP_GetBig16(msg + MAX_FIX_HEAD_SIZE + 3 + 1 + 2, &(str_connack->SysSigSetVersion));
		BP_ClientId = str_connack->ClientID;
	}
	return 0;
}

BP_INT16 BP_ParseFixHead(BP_UINT8 * msg, BP_UINT8 * type_and_flags, BP_UINT16 * rmn_len)
{
	BP_UINT8 i;
	BP_WORD multiplier;
	if(BP_NULL == msg) {
		return -0x1;
	}
	if(BP_NULL == type_and_flags) {
		return -0x2;
	}
	if(BP_NULL == rmn_len) {
		return -0x3;
	}
	i = 0;
	*type_and_flags = msg[i];

	multiplier = 1;
	*rmn_len = 0;
	do {
		i++;
		*rmn_len += (msg[i] & 0x7F) * multiplier;
		multiplier *= 128;
		if(multiplier > 128) {
			return -0x11;
		}
	} while((msg[i] & 0x80) != 0);

	if(*rmn_len < 128 && *rmn_len != 0) {
		*rmn_len -= 1;
	}

	return 0;
}

BP_INT8 BP_CheckCRC32(BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT32 crc;
	if(BP_NULL == msg) {
		return -0x01;
	}
	if(len < 4) {
		return -0x02;
	}
	BP_GetNet32(msg + len - 4, &crc);

	if(BP_calc_crc32(msg, len - 4) != crc) {
		return -0x11;
	}

	return 0;
}

BP_INT8 BP_CheckCRC16(BP_UINT8 * msg, BP_UINT16 len)
{
	BP_UINT16 crc;
	if(BP_NULL == msg) {
		return -0x01;
	}
	if(len < 2) {
		return -0x02;
	}
	BP_GetNet16(msg + len - 2, &crc);

	if(BP_calc_crc16(msg, len - 2) != crc) {
		return -0x11;
	}

	return 0;
}

BP_INT8 BP_CheckCRC(BP_UINT8 crc_flags, BP_UINT8 * msg, BP_UINT16 len)
{
	if(crc_flags & BP_FIX_FLAG_CRC16_MSK) {
		return BP_CheckCRC16(msg, len);
	} else {
		return BP_CheckCRC32(msg, len);
	}
}
