///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017-2020 Ansersion
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
/// @brief 	packet parsing functions header file. 
///         BP_ParseXXX parses the variable header and payload which is BP CRC checked OK.
///         And then put the info into the data struct for different BP packet.
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
	BP_UINT16 	Level;
	BP_UINT8 	Flags;
	BP_UINT16 	AlvTime;
	BP_UINT8 	Timeout;
	BP_UINT8 	RetCode;
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
	BP_UINT16 SeqId;
	BP_UINT8 SigNum;
	BP_SigValArrayEntry * SigValArray;
} BP_PostStr;

typedef struct BP_PostackStr {
	BP_UINT8 Flags;
	BP_UINT16 SeqId;
	BP_UINT8 RetCode;
	BP_UINT16 SigIdErr;
} BP_PostackStr;

typedef struct BP_PushStr {
    VrbHead_PUSH vrb;
    Payload_PUSH pld;
} BP_PushStr;

typedef struct BP_PushackStr {
    VrbHead_PUSHACK vrb;
    Payload_PUSHACK pld;
} BP_PushackStr;

typedef struct BP_RprtackStr {
	BP_UINT8 Flags;
	// BP_UINT16 ClientID;
	BP_UINT16 SigIdErr;
	BP_UINT16 SeqId;
	BP_UINT8 RetCode;
} BP_RprtackStr;

typedef struct BP_PingackStr {
	BP_UINT8 Flags;
	// BP_UINT16 ClientID;
	BP_UINT16 SeqId;
	BP_UINT8 RetCode;
} BP_PingackStr;

typedef struct BP_SpecsetStr {
	BP_UINT16 Type;
	BP_UINT16 SeqId;
    BP_UINT8 SsidLen;
    BP_UINT8 * Ssid;
    BP_UINT8 PasswordLen;
    BP_UINT8 * Password;
    BP_UINT8 UserNameLen;
    BP_UINT8 * UserName;
} BP_SpecsetStr;

typedef struct BP_SpecackStr {
	BP_UINT16 Type;
	BP_UINT8 RetCode;
} BP_SpecackStr;

/** 
  * @Brief BP_ParsePingack parse message recevied into BP_PingackStr
  * @Param bp_context   the BP context
  * @Param [out]str_pingack   struct to record info from the BP PINGACK message
  * @Param msg  message recevied
  * @Param len  message length
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT8 BP_ParsePingack(BPContext * bp_context, BP_PingackStr * str_pingack, BP_UINT8 * msg, BP_UINT16 len);

/** 
  * @Brief BP_ParseRprtack parse message recevied into BP_RprtackStr
  * @Param bp_context   the BP context
  * @Param [out]str_rprtack   struct to record info from the BP RPRTACK message
  * @Param msg  message recevied
  * @Param len  message length
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT8 BP_ParseRprtack(BPContext * bp_context, BP_RprtackStr * str_rprtack, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParsePost(BP_PostStr * str_post, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParsePostack(BPContext * bp_context, BP_PostackStr * str_postack, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParseGet(BP_GetStr * str_get, BP_UINT8 * msg, BP_UINT16 len);
EXPORT_API BP_INT8 BP_ParsePush(BPContext * bp_context, BP_PushStr * str_push, BP_UINT8 * msg, BP_UINT16 len);

/** 
  * @Brief BP_ParseConnack parse message recevied into BP_ConnackStr
  * @Param bp_context   the BP context
  * @Param [out]str_connack   struct to record info from the BP CONNACK message
  * @Param msg  message recevied
  * @Param len  message length
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT8 BP_ParseConnack(BPContext * bp_context, BP_ConnackStr * str_connack, BP_UINT8 * msg, BP_UINT16 len);

/** 
  * @Brief BP_ParseSpecset parse message recevied into BP_SpecsetStr
  * @Param bp_context   the BP context
  * @Param [out]str_specset   struct to record info from the BP SPECSET message
  * @Param msg  message recevied
  * @Param len  message length
  * @return Success     0
  *         Failed      minus number(such as '-1')
 */
EXPORT_API BP_INT8 BP_ParseSpecset(BPContext * bp_context, BP_SpecsetStr * str_specset, BP_UINT8 * msg, BP_UINT16 len);

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

EXPORT_API BP_UINT8 * ParseServerNode(BPServerNode * server_node, BP_UINT8 * msg);

#endif

