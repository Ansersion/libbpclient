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
#define BP_TRUE 	1
#define BP_FALSE 	0

#ifdef WIN32
#define EXPORT_API __declspec(dllexport) 
#else
#define EXPORT_API
#endif


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
	typedef unsigned char           BP_UINT8;
	typedef char                    BP_INT8;
	typedef unsigned short          BP_UINT16;
	typedef short                   BP_INT16;
	typedef unsigned int            BP_UINT32;
	typedef int                     BP_INT32;
	typedef unsigned long long      BP_UINT64;
	typedef long long               BP_INT64;
	typedef float                   BP_FLOAT;
	#define BP_WORD 	BP_UINT64

#elif defined BP_CPU32
	typedef unsigned char       BP_UINT8;
	typedef char                BP_INT8; 	
	typedef unsigned short      BP_UINT16;
	typedef short               BP_INT16;
	typedef unsigned int        BP_UINT32;
	typedef int                 BP_INT32;
	typedef float               BP_FLOAT;
    #define BP_WORD             BP_UINT32    

#elif defined BP_CPU16
	typedef unsigned char       BP_UINT8;
	typedef char                BP_INT8;	
	typedef unsigned short      BP_UINT16;
	typedef short               BP_INT16; 	
	typedef unsigned long       BP_UINT32; 	
	typedef long                BP_INT32; 	
	typedef float               BP_FLOAT; 	
	#define BP_WORD 	BP_UINT16

#elif defined BP_CPU8
	typedef unsigned char       BP_UINT8;
	typedef char                BP_INT8; 	
	typedef unsigned short      BP_UINT16; 	
	typedef short               BP_INT16; 	
	typedef unsigned long       BP_UINT32;	
	typedef long                BP_INT32; 	
	typedef float               BP_FLOAT; 	
	#define BP_WORD 	BP_UINT8

#else
#error Please define your cpu macro first: BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8

#endif

#define BP_BOOL     BP_UINT8

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
    #define ENCRYPTION_NONE
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
    #define CHECKSUM_CRC32
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
    #define PERFORMANCE_LIMIT_STRONG
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
    #define DEBUG_MODE_ENABLE
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
    #define CLIENT_DEVICE
	#define CLIENT_TYPE 1
#endif

/** 
  * @Brief: BP_LEVEL determines the version number of BP
  * @Note: DEFAULT 0
 */
#define BP_LEVEL 	0

/** 
  * @Brief: BP_TIMEOUT determines the timeout of a packet
  *         In unit of second.
  * @Note: DEFAULT 5
 */
#define BP_TIMEOUT     5

/** 
  * @Brief: BP_ALIVE_PERIOD determines the alive time which is the interval between two BPPackets.
  *         The device client will send BPPing if there is no packets send during (BP_ALIVE_PERIOD - BP_TIMEOUT) second.
  *         In unit of second.
  * @Note: DEFAULT 60
 */
#define BP_ALIVE_PERIOD     60


#endif

