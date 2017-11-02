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

#endif

