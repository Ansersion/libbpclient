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
/// @file 	bp_public.h
/// @brief 	public tool functions header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_PUBLIC_H
#define __BP_PUBLIC_H

#include <bpclient_config.h>

#define BP_LEVEL 	0
#define BP_CLIENT_ID_LEN 	2
#define BP_CLIENT_ID_APPLY 	0

#define BP_SetBig16 	BP_SetNet16
#define BP_SetBig32 	BP_SetNet32

#define BP_GetBig16 	BP_GetNet16
#define BP_GetBig32 	BP_GetNet32

typedef struct PackBuf {
	// BP_UINT8 FxHdType;
	// BP_UINT8 FxHdRmnLen[2];
	BP_UINT8 * Buf;
	BP_WORD RmnLen;
	BP_UINT8 * PackStart;
	BP_WORD MsgSize;
	BP_WORD BufSize;
} PackBuf;

// variable struct
typedef struct VrbHead_CONNECT {
	BP_UINT16 	Level;
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	AlvTime;
	BP_UINT8 	Timeout;
} VrbHead_CONNECT;

typedef struct VrbHead_PING {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqID;
} VrbHead_PING;

typedef struct VrbHead_PINGACK {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqID;
} VrbHead_PINGACK;

typedef struct VrbHead_DISCONN {
	BP_UINT16 	ClntId;
} VrbHead_DISCONN;

typedef union vrbU {
	VrbHead_CONNECT 	CONNECT;
	VrbHead_DISCONN 	DISCONN;
	VrbHead_PING 		PING;
	VrbHead_PINGACK 	PINGACK;
}vrbU; 

typedef struct BPPackVrbHead {
	vrbU u;
} BPPackVrbHead;

// payload
typedef struct Payload_CONNECT {
	BP_UINT8 	NameLen;
	BP_UINT8 * 	Name;
	BP_UINT8  	PwdLen;
	BP_UINT8 * 	Pwd;
	BP_UINT8  	ClntIdLen;
	BP_UINT16 	ClntId;
} Payload_CONNECT;

// typedef struct Payload_DISCONN {
// 	FIELD_NULL();
// } Payload_DISCONN;

typedef union pldU {
	Payload_CONNECT 	CONNECT;
	// Payload_DISCONN 	DISCONN;
}pldU; 

typedef struct BPPackPayload {
	pldU u;
} BPPackPayload;

BP_UINT8 * BP_SetNet16(BP_UINT8 * dst, BP_UINT16 val);
BP_UINT8 * BP_SetNet32(BP_UINT8 * dst, BP_UINT32 val);

BP_UINT8 * BP_Set2ByteField(BP_UINT8 * pack, BP_UINT8 * field, BP_UINT16 field_len);

BP_UINT8 * BP_GetNet16(BP_UINT8 * src, BP_UINT16 * val);
BP_UINT8 * BP_GetNet32(BP_UINT8 * src, BP_UINT32 * val);

BP_UINT8 * BP_Get2ByteField(BP_UINT8 * pack, BP_UINT8 * field_buf, BP_UINT16 * field_len);
#endif

