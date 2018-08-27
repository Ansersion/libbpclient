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
/// @file 	bpclient_config.h
/// @brief 	configurations for different platforms
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPCLIENT_CONFIG_H
#define __BPCLIENT_CONFIG_H


#define BP_NULL 	0


// #define BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8, MUST BE DEFINED BY YOUR OWN
// #define ENCRYPTION_NONE/ENCRYPTION_BASE64, default ENCRYPTION_NONE
// #define CHECKSUM_CRC32/CHECKSUM_CRC16, default CHECKSUM_CRC32
// #define PERFORMANCE_LIMIT_NONE/PERFORMANCE_LIMIT_WEAK/PERFORMANCE_LIMIT_STRONG, default PERFORMANCE_LIMIT_STRONG
// #define DEBUG_MODE_ENABLE/DEBUG_MODE_DISABLE, default DEBUG_MODE_DISABLE 
// #define CLIENT_DEVICE, default CLIENT_DEVICE


/** 
  * @Brief: BPCPUXX define determine the cpu type
  * @Note: Must define one of "BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8" to match your cpu, NO DEFAULT VALUE
 */

#ifdef BP_CPU64
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned int
	#define BP_INT32 	int
	#define BP_UINT64 	unsigned long
	#define BP_INT64 	long
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT64

#elif defined BP_CPU32
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned int
	#define BP_INT32 	int
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT32

#elif defined BP_CPU16
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned long
	#define BP_INT32 	long
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT16

#elif defined BP_CPU8
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned long
	#define BP_INT32 	long
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT8

#else
#error Please define your cpu macro first: BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8

#endif

/** 
  * @Brief: ENCRYPTION_TYPE determines the cpu type
  * @Note: May define one one "ENCRYPTION_NONE/ENCRYPTION_BASE64" to encrypt your message when communicating with BCServer. 
  *        The higher the encryption strength is, the more resources("bandwidth/CPU") consume. DEFAULT ENCRYPTION_NONE
 */
#ifdef ENCRYPTION_NONE
	#define ENCRYPTION_TYPE 0
#elif defined ENCRYPTION_BASE64 
	#define ENCRYPTION_TYPE 1
#else 
	#define ENCRYPTION_TYPE 0
#endif

/** 
  * @Brief: CHECKSUM_TYPE determines the checksum type when transmitting BP packets
  * @Note: DEFAULT CHECKSUM_CRC32
 */
#ifdef CHECKSUM_CRC32
	#define CHECKSUM_TYPE 0
#elif defined CHECKSUM_CRC16 
	#define CHECKSUM_TYPE 1
#else 
	#define CHECKSUM_TYPE 0
#endif

/** 
  * @Brief: PERFORMANCE_LIMIT determines the machine ability
  * @Note: DEFAULT PERFORMANCE_LIMIT_STRONG
 */
#ifdef PERFORMANCE_LIMIT_NONE
	#define PERFORMANCE_LIMIT 0
#elif defined PERFORMANCE_LIMIT_WEAK 
	#define PERFORMANCE_LIMIT 1
#elif defined PERFORMANCE_LIMIT_STRONG
	#define PERFORMANCE_LIMIT 2
#else
	#define PERFORMANCE_LIMIT 2
#endif

/** 
  * @Brief: DEBUG_MODE determines the working state when the machine connects to BCServer.
  * 		When DEBUG_MODE_ENABLE is set, the BCServer will not store the info of the machine into its database.
  * @Note: DEFAULT DEBUG_MODE_DISABLE
 */
#ifdef DEBUG_MODE_ENABLE
	#define DEBUG_MODE 1
#elif defined DEBUG_MODE_DISABLE
	#define DEBUG_MODE 0
#else
	#define DEBUG_MODE 0
#endif

/** 
  * @Brief: CLIENT_TYPE determines whether the machine is user or device.
  * @Note: DEFAULT CLIENT_DEVICE
  * @Warning: only CLIENT_DEVICE supported noew(2018.06.05)
 */
#ifdef CLIENT_DEVICE
	#define CLIENT_TYPE 1
#elif defined CLIENT_USER
	#error Only support CLIENT_DEVICE
#else
	#define CLIENT_TYPE 1
#endif

#endif

/** 
  * @Brief: BP_LEVEL determines the version number of BP
  * @Note: DEFAULT 0
 */
#define BP_LEVEL 	0

