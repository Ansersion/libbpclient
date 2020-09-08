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
#include <bp_server_chain.h>

// #define BP_CLIENT_ID_LEN 	2
// #define BP_CLIENT_ID_APPLY 	0
// 
// #define BP_ENCRYPTION_PLAINTEXT     0x00
// #define BP_ENCRYPTION_BASE64      0x01
// 
// #define BP_CRC_TYPE_32      0x00
// #define BP_CRC_TYPE_16      0x01
// 
// #define BP_PERF_LIMIT_UNLIMIT   0x00
// #define BP_PERF_LIMIT_WEAK      0x01
// #define BP_PERF_LIMIT_STRONG    0x02
// #define BP_PERF_LIMIT_INVALID   0x03
// #define BP_PERF_LIMIT_HARD 	2

#define BP_BUF_SIZE 	1024
#define BP_BUF_SIZE_EMBEDED 	1024
#define BP_NAME_SIZE 	65
#define BP_PASSWORD_SIZE 	65

#define BP_SetBig16 	BP_SetNet16
#define BP_SetBig32 	BP_SetNet32

#define BP_GetBig16 	BP_GetNet16
#define BP_GetBig32 	BP_GetNet32

// #define MAX_FIX_HEAD_SIZE 	3
// #define MIN_FIX_HEAD_SIZE 	2

#define FIX_HEAD_SIZE 	3

#if CHECKSUM_TYPE == 0
	#define CHECKSUM_SIZE 4
#elif defined CHECKSUM_TYPE == 1
	#define CHECKSUM_SIZE 2
#else
	#error CHECKSUM_TYPE unconfigured(refer to bpclient_config.h)
#endif

#define PACK_SEQ_MIN  1
#define PACK_SEQ_MAX  0xFFFF

#define SET_PACK_SEQ(x, y) if(!(x = y++)) { \
    y = PACK_SEQ_MIN; \
    x = PACK_SEQ_MIN; \
}

typedef void (*SwitchTypeDoClbk)(void * para);

typedef struct PackBuf {
	BP_UINT8 * Buf; /*!< packet buffer, if set, not changed */
	BP_WORD BufSize; /*!< packet buffer size, if set, not changed */
	BP_WORD RmnLen; /*!< remaining length of BPPacket */
	BP_UINT8 * PackStart; /*!< a moving pointer for constructing BP packet*/
	BP_WORD MsgSize; /*!< The size of BPPacket in parameter "Buf" */
} PackBuf;

typedef struct BPContext {
    /* suggest: not change these variables durring time */
    BP_UINT8 Encryption;
    BP_UINT8 CrcType;
    BP_UINT8 BPLevel;
    BP_UINT8 PerformanceLimit;
    BP_UINT8 ClientType;
    /* suggest end */

    /* note: changed and token into effect only after a new CONNECTION */
    BP_UINT16 BPAlivePeroid;
    BP_UINT16 BPTimeout;
    /* note end */

    PackBuf * packBuf;
    BP_UINT8 * name;
    BP_UINT8 * password;
	
	/* seq id */
	BP_UINT16 SeqIDComm;
	BP_UINT16 SeqIDPing;
	BP_UINT16 SeqIDReport;

    /* server chain*/
    BPServerNode * ServerChain;
    BP_WORD ServerChainSize;
    BP_UINT8 CurrentServerNodeIndex;
    BP_UINT16 SysSigTableVersion;

    /* admin user */
    BP_UINT16 AdminNameLen;
    BP_UINT8 * AdminName;

    /* Device info */
    BP_UINT32 devId;

} BPContext;

// variable struct
typedef struct VrbHead_CONNECT {
	BP_UINT16 	Level;
	BP_UINT8 	Flags;
	// BP_UINT16 	ClntId;
	BP_UINT16 	AlvTime;
	BP_UINT8 	Timeout;
} VrbHead_CONNECT;

typedef struct VrbHead_GETACK {
	BP_UINT8 	Flags;
	// BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
	BP_UINT8 	RetCode;
} VrbHead_GETACK;

typedef struct VrbHead_POST {
	BP_UINT8 	Flags;
	// BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_POST;

typedef struct VrbHead_POSTACK {
	BP_UINT8 	Flags;
	// BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
	BP_UINT8 	RetCode;
} VrbHead_POSTACK;

typedef struct VrbHead_REPORT {
	BP_UINT8 	Flags;
	BP_UINT16 	SeqId;
} VrbHead_REPORT;

typedef struct VrbHead_RPRTACK {
	BP_UINT8 	Flags;
	BP_UINT16 	SeqId;
	BP_UINT8 	RetCode;
} VrbHead_RPRTACK;

typedef struct VrbHead_PING {
	BP_UINT8 	Flags;
	// BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_PING;

typedef struct VrbHead_PINGACK {
	BP_UINT8 	Flags;
	// BP_UINT16 	ClntId;
	BP_UINT16 	SeqId;
} VrbHead_PINGACK;

typedef struct VrbHead_DISCONN {
	BP_UINT8 	Flags;
} VrbHead_DISCONN;

typedef struct VrbHead_SPECACK {
	BP_UINT16 	Type;
	BP_UINT8 	RetCode;
    BP_UINT16   SeqId;
} VrbHead_SPECACK;

typedef struct VrbHead_SPECSET {
	BP_UINT16 	Type;
} VrbHead_SPECSET;

typedef union vrbU {
	VrbHead_CONNECT 	CONNECT;
	VrbHead_GETACK 		GETACK;
	VrbHead_PING 		PING;
	VrbHead_PINGACK 	PINGACK;
	VrbHead_REPORT 		REPORT;
	VrbHead_RPRTACK 	RPRTACK;
	VrbHead_DISCONN 	DISCONN;
	VrbHead_POST 		POST;
	VrbHead_POSTACK 	POSTACK;
	VrbHead_SPECSET 	SPECSET;
	VrbHead_SPECACK 	SPECACK;
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
	BP_UINT16  	SysSigTableVersion;
	BP_UINT16 	AdminNameLen;
	BP_UINT8 *	AdminName;
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
	BP_UINT32 	DevId;
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
	BP_UINT16 SigValEleNum;
	const BP_SigId2Val * SigArray;
	BP_UINT16 SysSigMapEleNum;
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

typedef struct BPPacket {
	vrbU vrb;
	pldU pld;
} BPPacket;


EXPORT_API extern BPContext BPContextEmbeded;
// extern BP_UINT8 BP_Buf[];
EXPORT_API extern BP_UINT8 BPBufEmbeded[BP_BUF_SIZE_EMBEDED];
EXPORT_API extern BP_UINT8 BPNameEmbeded[BP_NAME_SIZE];
EXPORT_API extern BP_UINT8 BPPasswordEmbeded[BP_PASSWORD_SIZE];

/* 3 temporary server address buffer */
EXPORT_API extern PackBuf PackBufEmbeded;
// extern BP_UINT16 BP_ClientId;

// typedef struct BP_Param {
// 	BP_UINT8 ClientType;
// 	BP_UINT16 AliveTime;
// 	BP_UINT8 Timeout;
// } BP_Param;
EXPORT_API extern BP_UINT8 BP_CrcType;
EXPORT_API extern BP_UINT8 BP_ClientType;
EXPORT_API extern BP_UINT8 BP_CipherType;
EXPORT_API extern BP_UINT16 BP_AliveTime;
EXPORT_API extern BP_UINT8 BP_Timeout;
EXPORT_API extern BP_UINT16 BP_SysSigSetVersion;

EXPORT_API extern BP_UINT16 BP_SeqIdCommon;
EXPORT_API extern BP_UINT16 BP_SeqIdGet;
EXPORT_API extern BP_UINT16 BP_SeqIdPost;
EXPORT_API extern BP_UINT16 BP_SeqIdReport;
EXPORT_API extern BP_UINT16 BP_SeqIdPing;



EXPORT_API BP_UINT8 * BP_SetNet16(BP_UINT8 * dst, BP_UINT16 val);
EXPORT_API BP_UINT8 * BP_SetNet32(BP_UINT8 * dst, BP_UINT32 val);
EXPORT_API BP_UINT8 * BP_SetNBytes(BP_UINT8 * dst, BP_UINT8 * src, BP_WORD num);

EXPORT_API BP_UINT8 * BP_Set2ByteField(BP_UINT8 * pack, BP_UINT8 * field, BP_UINT16 field_len);
EXPORT_API BP_UINT8 * BP_Set1ByteField(BP_UINT8 * pack, const BP_UINT8 * field, BP_UINT8 field_len);

EXPORT_API BP_UINT8 * BP_GetNet16(BP_UINT8 * src, BP_UINT16 * val);
EXPORT_API BP_UINT8 * BP_GetNet32(BP_UINT8 * src, BP_UINT32 * val);

EXPORT_API BP_UINT8 * BP_Get2ByteField(BP_UINT8 * pack, BP_UINT8 * field_buf, BP_UINT16 * field_len);

EXPORT_API BP_WORD sortSig2ValClbk(void * a, void * b);
EXPORT_API void BP_SigvalSort(const BP_SigId2Val * sig_array, BP_WORD num);

EXPORT_API BPContext * getBPContextEmbeded();

#endif

