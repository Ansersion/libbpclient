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
/// @file 	bp_pack_type.h
/// @brief 	macros for BP packet type
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_PACK_TYPE_H
#define __BP_PACK_TYPE_H

#define BP_PACK_TYPE_CONNECT 	1
#define BP_PACK_TYPE_CONNACK 	2
#define BP_PACK_TYPE_GET 		3
#define BP_PACK_TYPE_GETACK 	4
#define BP_PACK_TYPE_POST 		5
#define BP_PACK_TYPE_POSTACK 	6
#define BP_PACK_TYPE_REPORT 	7
#define BP_PACK_TYPE_RPRTACK 	8
#define BP_PACK_TYPE_PING 		9
#define BP_PACK_TYPE_PINGACK 	10
#define BP_PACK_TYPE_PUSH 		11
#define BP_PACK_TYPE_PUSHACK 	12
#define BP_PACK_TYPE_DISCONN 	13

#define BP_PACK_TYPE_CONNECT_MSK 	(BP_PACK_TYPE_CONNECT 	<< 4)
#define BP_PACK_TYPE_CONNACK_MSK 	(BP_PACK_TYPE_CONNACK 	<< 4)
#define BP_PACK_TYPE_GET_MSK 		(BP_PACK_TYPE_GET 		<< 4)
#define BP_PACK_TYPE_GETACK_MSK 	(BP_PACK_TYPE_GETACK 	<< 4)
#define BP_PACK_TYPE_POST_MSK 		(BP_PACK_TYPE_POST 		<< 4)
#define BP_PACK_TYPE_POSTACK_MSK 	(BP_PACK_TYPE_POSTA 	<< 4)
#define BP_PACK_TYPE_REPORT_MSK 	(BP_PACK_TYPE_REPORT 	<< 4)
#define BP_PACK_TYPE_RPRTACK_MSK 	(BP_PACK_TYPE_RPRTACK 	<< 4)
#define BP_PACK_TYPE_PING_MSK 		(BP_PACK_TYPE_PING 		<< 4)
#define BP_PACK_TYPE_PINGACK_MSK 	(BP_PACK_TYPE_PINGACK 	<< 4)
#define BP_PACK_TYPE_PUSH_MSK 		(BP_PACK_TYPE_PUSH 		<< 4)
#define BP_PACK_TYPE_PUSHACK_MSK 	(BP_PACK_TYPE_PUSHACK 	<< 4)
#define BP_PACK_TYPE_DISCONN_MSK 	(BP_PACK_TYPE_DISCONN 	<< 4)

#endif

