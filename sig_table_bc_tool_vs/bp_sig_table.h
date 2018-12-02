///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017-2018 Ansersion
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

#include <bp_sig_str.h>

#define SIG_SYS_SERIAL_NUMBER 		0xE000
#define SIG_SYS_COMM_STATE 			0xE001
#define SIG_SYS_POWER 				0xE002
#define SIG_SYS_STRENGTH            0xE005

extern BP_SigId2Val * g_SysSigId2Val;
extern BP_SigTable * g_SysSigTable;
extern BP_WORD g_SysSigNum;

extern BP_SysCustomUnit * g_SysCustomUnitTable;
extern BP_WORD g_SysCustomUnitNum;

extern BP_UINT8 g_SysMapDis_0[];
extern BP_SysSigMap * g_SysSigMap;
extern BP_WORD g_SysSigMapSize;

EXPORT_API void BP_SetSysSigId2ValTable(BP_SigId2Val * cus_sig_id_2_val, BP_WORD cus_sig_num);
EXPORT_API void BP_SetSysSigTable(BP_SigTable * cus_sig_table);
EXPORT_API void BP_SetSysCustomUnitTable(BP_SysCustomUnit * sys_custom_unit_table, BP_WORD sys_custom_unit_table_num);
EXPORT_API void BP_SetSysSigMap(BP_SysSigMap * sys_sig_map, BP_WORD sys_sig_map_size);

#endif

