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
/// @file 	bp_sig_table.h
/// @brief 	struct for signal table
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_SIG_TABLE_H
#define __BP_SIG_TABLE_H

#include <bpclient_config.h>

typedef union SigTypeU {
	BP_UINT32 	t_u32;
	BP_UINT16 	t_u16;
	BP_INT32 	t_i32;
	BP_INT16 	t_i16;
	BP_UINT16 	t_enm;
	BP_FLOAT 	t_flt;
	BP_UINT8* 	t_str;
} SigTypeU;

typedef struct BP_SysSigTable {
	// 0-t_u32;
	// 1-t_u16;
	// 2-t_i32;
	// 3-t_i16;
	// 4-t_enm;
	// 5-t_flt;
	// 6-t_str;
	BP_UINT32 SigType:4;
	BP_UINT32 EnStatics:1;
	BP_UINT32 Accuracy:3;
	// BP_UINT32 EnAlarm:1;
	// BP_UINT32 AlmClass:3;
	BP_UINT32 Reserved:24;
	SigTypeU MinVal;
	SigTypeU MaxVal;
	SigTypeU DefVal;
} BP_SysSigTable;

typedef struct BP_CusSigTable {
	BP_UINT16 SigID;
	BP_SysSigTable SigTab;
} BP_CumSigTable;

#endif

