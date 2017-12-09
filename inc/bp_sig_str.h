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
/// @file 	bp_sig_str.h
/// @brief 	struct for signal table
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_SIG_STR_H
#define __BP_SIG_STR_H

#include <bpclient_config.h>

#define DIST_END_FLAG_MSK 	0x01

#define DIST_CLASS_MSK 		0x0E	
#define DIST_CLASS_1_MSK 	0x02	
#define DIST_CLASS_2_MSK 	0x04	
#define DIST_CLASS_3_MSK 	0x06	
#define DIST_CLASS_4_MSK 	0x08	
#define DIST_CLASS_5_MSK 	0x0A	
#define DIST_CLASS_6_MSK 	0x0C	

typedef enum BP_SigType {
	SIG_TYPE_U32 = 0, 
	SIG_TYPE_U16,
	SIG_TYPE_I32, 
	SIG_TYPE_I16, 
	SIG_TYPE_ENM, 
	SIG_TYPE_FLT, 
	SIG_TYPE_STR, 
} BP_SigType;

typedef enum BP_SigPerm {
	SIG_PERM_RO = 0, 
	SIG_PERM_RW, 
} BP_SigPerm;

typedef union SigTypeU {
	BP_UINT32 	t_u32;
	BP_UINT16 	t_u16;
	BP_INT32 	t_i32;
	BP_INT16 	t_i16;
	BP_UINT16 	t_enm;
	BP_FLOAT 	t_flt;
	BP_UINT8* 	t_str;
} SigTypeU;

typedef struct BP_SigId2Val {
	BP_UINT16 SigId;
	SigTypeU SigVal;
}BP_SigId2Val;

typedef struct BP_SigTable {
	BP_UINT16 SigId;
	/* SIG_TYPE_U32 = 0, */
	/* SIG_TYPE_U16,*/
	/* SIG_TYPE_i32, */
	/* SIG_TYPE_i16, */
	/* SIG_TYPE_ENM, */
	/* SIG_TYPE_FLT, */
	/* SIG_TYPE_STR, */
	BP_UINT16 SigType:4;
	BP_UINT16 EnStatics:1;
	BP_UINT16 Accuracy:3;
	// BP_UINT32 EnAlarm:1;
	// BP_UINT32 AlmClass:3;
	/* SIG_PERM_RO = 0, */
	/* SIG_PERM_RW, */
	BP_UINT16 Perm:1;
	BP_UINT16 Reserved:7;
	SigTypeU * MinVal;
	SigTypeU * MaxVal;
	SigTypeU * DefVal;
} BP_SigTable;

typedef struct BP_CusSigTable {
	BP_UINT16 SigID;
	BP_SigTable SigTab;
} BP_CumSigTable;

typedef struct BP_SysSigMap {
	BP_UINT8 Dist;
	BP_UINT8 SigMapSize;
	const BP_UINT8 * SigMap;
} BP_SysSigMap;

#endif

