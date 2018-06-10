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
#include <bp_sig_str.h>
#include <bp_utils.h>

#define BP_LEVEL 	0
#define BP_CLIENT_ID_LEN 	2
#define BP_CLIENT_ID_APPLY 	0

#define BP_BUF_SIZE 	1024
#define BP_NAME_SIZE 	65
#define BP_PASSWORD_SIZE 	65

#define BP_SetBig16 	BP_SetNet16
#define BP_SetBig32 	BP_SetNet32

#define BP_GetBig16 	BP_GetNet16
#define BP_GetBig32 	BP_GetNet32

#define MAX_FIX_HEAD_SIZE 	3
#define MIN_FIX_HEAD_SIZE 	2

#define FIX_HEAD_SIZE 	3

#if CHECKSUM_TYPE == 0
	#define CHECKSUM_SIZE 4
#elif defined CHECKSUM_TYPE == 1
	#define CHECKSUM_SIZE 2
#else
	#error CHECKSUM_TYPE unconfigured(refer to bpclient_config.h)
#endif

typedef void (*SwitchTypeDoClbk)(void * para);


typedef struct PackBuf {
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

typedef struct VrbHead_GETACK {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
	BP_UINT8 	RetCode;
} VrbHead_GETACK;

typedef struct VrbHead_POST {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_POST;

typedef struct VrbHead_POSTACK {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
	BP_UINT8 	RetCode;
} VrbHead_POSTACK;

typedef struct VrbHead_REPORT {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_REPORT;

typedef struct VrbHead_PING {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_PING;

typedef struct VrbHead_PINGACK {
	BP_UINT8 	Flags;
	BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_PINGACK;

typedef struct VrbHead_DISCONN {
	BP_UINT16 	ClntId;
} VrbHead_DISCONN;

typedef union vrbU {
	VrbHead_CONNECT 	CONNECT;
	VrbHead_GETACK 		GETACK;
	VrbHead_PING 		PING;
	VrbHead_PINGACK 	PINGACK;
	VrbHead_REPORT 		REPORT;
	VrbHead_DISCONN 	DISCONN;
	VrbHead_POST 		POST;
	VrbHead_POSTACK 	POSTACK;
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

typedef struct Payload_GETACK {
	BP_UINT8 	SigNum;
	BP_SigType 	* SigTypeArray;
	BP_SigId2Val * SigArray;
} Payload_GETACK;

// typedef struct Payload_DISCONN {
// 	FIELD_NULL();
// } Payload_DISCONN;

// typedef struct BP_SysSigMap {
// 	BP_UINT8 Dist;
// 	BP_UINT8 SigMapSize;
// 	BP_UINT8 *SigMap;
// } BP_SysSigMap;

typedef struct Payload_POST {
	BP_UINT8 	SigNum;
	BP_SigType 	* SigTypeArray;
	BP_SigId2Val * SigArray;
} Payload_POST;

typedef struct Payload_POSTACK {
	BP_UINT32 Reserved;
} Payload_POSTACK;

typedef struct Payload_PING {
	BP_UINT32 Reserved;
} Payload_PING;

typedef struct Payload_REPORT {
	BP_UINT8 * DevName;
	BP_UINT8 DevNameLen;
	BP_UINT32 SigTabChkCrc;
	BP_UINT16 SysSigValEleNum;
	BP_UINT16 CusSigValEleNum;
	const BP_SigId2Val * SysSigArray;
	const BP_SigId2Val * CusSigArray;
	const BP_SysSigMap * SysSigMap;
} Payload_REPORT;

typedef union pldU {
	Payload_CONNECT 	CONNECT;
	Payload_GETACK 		GETACK;
	Payload_REPORT 		REPORT;
	Payload_POST 		POST;
	Payload_POSTACK 	POSTACK;
	Payload_PING 		PING;
	// Payload_DISCONN 	DISCONN;
}pldU; 

typedef struct BPPackPayload {
	pldU u;
} BPPackPayload;


extern BP_UINT8 BP_Buf[];
extern BP_UINT8 BP_Name[BP_NAME_SIZE];
extern BP_UINT8 BP_Password[BP_PASSWORD_SIZE];
extern BP_UINT8 BP_DEV_NAME[];
extern PackBuf BP_Pack_Buf;
extern BP_UINT16 BP_ClientId;

// typedef struct BP_Param {
// 	BP_UINT8 ClientType;
// 	BP_UINT16 AliveTime;
// 	BP_UINT8 Timeout;
// } BP_Param;
extern BP_UINT8 BP_CrcType;
extern BP_UINT8 BP_ClientType;
extern BP_UINT8 BP_CipherType;
extern BP_UINT16 BP_AliveTime;
extern BP_UINT8 BP_Timeout;
extern BP_UINT16 BP_SysSigSetVersion;

extern BP_UINT16 BP_SeqIdCommon;
extern BP_UINT16 BP_SeqIdGet;
extern BP_UINT16 BP_SeqIdPost;
extern BP_UINT16 BP_SeqIdReport;
extern BP_UINT16 BP_SeqIdPing;



BP_UINT8 * BP_SetNet16(BP_UINT8 * dst, BP_UINT16 val);
BP_UINT8 * BP_SetNet32(BP_UINT8 * dst, BP_UINT32 val);
BP_UINT8 * BP_SetNBytes(BP_UINT8 * dst, BP_UINT8 * src, BP_WORD num);

BP_UINT8 * BP_Set2ByteField(BP_UINT8 * pack, BP_UINT8 * field, BP_UINT16 field_len);

BP_UINT8 * BP_GetNet16(BP_UINT8 * src, BP_UINT16 * val);
BP_UINT8 * BP_GetNet32(BP_UINT8 * src, BP_UINT32 * val);

BP_UINT8 * BP_Get2ByteField(BP_UINT8 * pack, BP_UINT8 * field_buf, BP_UINT16 * field_len);

BP_WORD sortSig2ValClbk(void * a, void * b);
void BP_SigvalSort(const BP_SigId2Val * sig_array, BP_WORD num);

#endif

