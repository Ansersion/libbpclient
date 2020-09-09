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
/// @file 	bp_vrb_flags.h
/// @brief 	macros for BP variable head flags
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_VRB_FLAGS_H
#define __BP_VRB_FLAGS_H

#include <bpclient_config.h>

// for CONNECT
#define BP_VRB_FLAG_USER_NAME_MSK 	(1 << 7)
#define BP_VRB_FLAG_PASSWORD_MSK 	(1 << 6)
#define BP_VRB_FLAG_USER_CLNT_MSK 	(1 << 2)
#define BP_VRB_FLAG_DEV_CLNT_MSK 	(1 << 1)
// #define BP_VRB_FLAG_CLNT_TYPE_MSK 	(1 << CLIENT_TYPE)
// #define BP_VRB_FLAG_PERM_LMT_MSK 	(PER)

// for CONNACK 
#define BP_VRB_FLAG_NEW_CLNT_ID_MSK 	(1 << 7)
#define BP_VRB_FLAG_SNG_DEV_SERV_MSK 	(1 << 6)

// for GET, GETACK
#define BP_VRB_FLAG_CHINESE_MSK 	(1 << 7)
#define BP_VRB_FLAG_ENGLISH_MSK 	(1 << 6)
#define BP_VRB_FLAG_FRENCH_MSK 		(1 << 5)
#define BP_VRB_FLAG_RUSSIAN_MSK 	(1 << 4)
#define BP_VRB_FLAG_ARABIC_MSK 		(1 << 3)
#define BP_VRB_FLAG_SPANISH_MSK 	(1 << 2)
#define BP_VRB_FLAG_OTHER_LAN_MSK 	(1 << 1)
#define BP_VRB_FLAG_SIG_SET_MSK 	(1 << 0)

// for POST
// #define BP_VRB_FLAG_DEV_CLNT_MSK (1 << 1): the same usage as CONNECT
#define BP_VRB_FLAG_POST_SIG_MSK 	(1 << 0):
#define BP_VRB_FLAG_RPRT_SIG_SET_MSK 	(1 << 0):

// for REPORT
#define BP_VRB_FLAG_DEV_NAME_MSK 	(1 << 7)
#define BP_VRB_FLAG_SYS_SIG_SET_MSK 	(1 << 7)
#define BP_VRB_FLAG_CUS_SIG_SET_MSK 	(1 << 6)
#define BP_VRB_FLAG_SIG_VAL_MSK 	(1 << 4)
#define BP_VRB_FLAG_SYS_SIG_ATTR_CUSTOM_MSK 	(1 << 2)
#define BP_VRB_FLAG_SIG_TAB_CHK_MSK 	(1 << 1)

// for PUSH
#define BP_VRB_FLAG_PUSH_SIGNAL_VALUE 	(1 << 4)

#endif

