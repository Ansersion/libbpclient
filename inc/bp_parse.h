///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017-2019 Ansersion
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
/// @file 	bp_parse.h
/// @brief 	packet parsing functions header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_PARSE_H
#define __BP_PARSE_H

#include <bp_public.h>
#include <bp_connack.h>

typedef struct BP_ConnackStr {
	BP_UINT8 	RetCode;
	BP_UINT16 	ClientID;
	BP_UINT16 	SysSigSetVersion;
} BP_ConnackStr;

typedef struct BP_GetStr {
	BP_UINT8 Flags;
	BP_UINT16 ClientID;
	BP_UINT16 SeqId;
	BP_UINT8 SigNum;
	BP_SigId2Val * SigTabArray;
} BP_GetStr;

typedef struct BP_PostStr {
	BP_UINT8 Flags;
	BP_UINT16 ClientID;
	BP_UINT16 SeqId;
	// BP_UINT8 SigTabNum;
	BP_UINT8 SigNum;
	// BP_SigId2Val * SigArray;
	BP_SigValArrayEntry * SigValArray;
} BP_PostStr;

typedef struct BP_RprtackStr {
	// BP_UINT8 Flags;
	// BP_UINT16 ClientID;
	BP_UINT16 SeqId;
	BP_UINT8 RetCode;
} BP_RprtackStr;

typedef struct BP_PingackStr {
	BP_UINT8 Flags;
	// BP_UINT16 ClientID;
	BP_UINT16 SeqId;
	BP_UINT8 RetCode;
} BP_PingackStr;

/** 
  * @Brief BP_ParsePingack parse message recevied into BP_PingackStr
  * @Param bp_connack   the BP context
  * @Param [out]str_pingack   struct to record info from the BP PINGACK message
  * @Param msg  message recevied
  * @Param len  message length
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT8 BP_ParsePingack(BPContext * bp_context, BP_PingackStr * str_pingack, BP_UINT8 * msg, BP_UINT16 len);
// BP_INT8 BP_ParseRprtack(BP_RprtackStr * str_rprtack, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParseRprtack(BPPacket * bp_packet, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParsePost(BP_PostStr * str_post, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParseGet(BP_GetStr * str_get, BP_UINT8 * msg, BP_UINT16 len);

/** 
  * @Brief BP_ParseConnack parse message recevied into BP_ConnackStr
  * @Param bp_connack   the BP context
  * @Param [out]str_connack   struct to record info from the BP CONNACK message
  * @Param msg  message recevied
  * @Param len  message length
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT8 BP_ParseConnack(BPContext * bp_context, BP_ConnackStr * str_connack, BP_UINT8 * msg, BP_UINT16 len);
/** 
  * @Brief BP_ParseFixHead parse fixed head for BP packet
  * @Param msg   pointer to the start of the buffer with fix head
  * @Param [out]type_and_flags   BP pack type and flags of in the fix head
  * @Param [out]rmn_len Remaining length in the fix head    
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT16 BP_ParseFixHead(BP_UINT8 * msg, BP_UINT8 * type_and_flags, BP_UINT16 * rmn_len);
#ifdef CHECKSUM_CRC32
EXPORT_API BP_INT8 BP_CheckCRC32(BP_UINT8 * msg, BP_UINT16 len);
#else
EXPORT_API BP_INT8 BP_CheckCRC16(BP_UINT8 * msg, BP_UINT16 len);
#endif
EXPORT_API BP_INT8 BP_CheckCRC(BP_UINT8 crc_flags, BP_UINT8 * msg, BP_UINT16 len);

#endif

