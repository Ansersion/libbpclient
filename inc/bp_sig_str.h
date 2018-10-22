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

#define ENABLE_ALARM            1
#define DISABLE_ALARM           0
#define ENABLE_STATISTICS       1
#define DISABLE_STATISTICS      0
#define ENABLE_DISPLAY          1
#define DISABLE_DISPLAY         0
#define HAS_CUSTOM_INFO         1
#define NO_CUSTOM_INFO          0
#define RESERVED_FIELD          0

#define ALARM_CLASS_NONE            0x7F
#define ALARM_CLASS_INFO            4    
#define ALARM_CLASS_ATTENTION       3
#define ALARM_CLASS_WARNING         2
#define ALARM_CLASS_SERIOUS         1
#define ALARM_CLASS_EMERGENCY       0

#define ALARM_DELAY_DEFAULT            5

#define SYS_SIG_CUSTOM_TYPE_ALM_DLY_AFTER       10
#define SYS_SIG_CUSTOM_TYPE_ALM_DLY_BEFORE      9
#define SYS_SIG_CUSTOM_TYPE_ALM_CLASS           8
#define SYS_SIG_CUSTOM_TYPE_IS_ALARM            7
#define SYS_SIG_CUSTOM_TYPE_DEF_VAL             6
#define SYS_SIG_CUSTOM_TYPE_MAX_VAL             5
#define SYS_SIG_CUSTOM_TYPE_MIN_VAL             4
#define SYS_SIG_CUSTOM_TYPE_ACCURACY            3
#define SYS_SIG_CUSTOM_TYPE_GROUP_LANG          2
#define SYS_SIG_CUSTOM_TYPE_ENUM_LANG           1
#define SYS_SIG_CUSTOM_TYPE_EN_STATISTICS       0

#define SIG_INDEX_INVALID 			0xFFFF

#define DIST_END_FLAG_MSK 	0x01

#define DIST_BASIC_MSK 	        0x00
#define DIST_TEMP_HUMIDITY_MSK 	0x10

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
	SIG_TYPE_BOOLEAN, 
	SIG_TYPE_UNKNOWN = 15,
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
	BP_UINT8 	t_bool;
} SigTypeU;

typedef struct BP_SigId2Val {
	BP_UINT16 SigId;
	SigTypeU SigVal;
}BP_SigId2Val;

typedef struct BP_SigValArrayEntry {
	BP_UINT16 SigIdx;
	BP_UINT16 SigId;
}BP_SigValArrayEntry;

typedef struct BP_SigTable {
	BP_UINT16 SigId;
	/* SIG_TYPE_U32 = 0, */
	/* SIG_TYPE_U16,*/
	/* SIG_TYPE_i32, */
	/* SIG_TYPE_i16, */
	/* SIG_TYPE_ENM, */
	/* SIG_TYPE_FLT, */
	/* SIG_TYPE_STR, */
	/* SIG_TYPE_BOOLEAN, */
	BP_UINT16 SigType:4;
	/* DISABLE_STATISTICS = 0, */
	/* ENABLE_STATISTICS, */
	BP_UINT16 EnStatics:1;
	/* DISABLE_DISPLAY = 0, */
	/* ENABLE_DISPLAY, */
	BP_UINT16 IsDisplay:1;
	BP_UINT16 Accuracy:3;
	/* DISABLE_ALARM = 0, */
	/* ENABLE_ALARM, */
	BP_UINT16 EnAlarm:1;
	/* SIG_PERM_RO = 0, */
	/* SIG_PERM_RW, */
	BP_UINT16 Perm:1;
    /* ALARM_CLASS_NONE = 5 */
    /* ALARM_CLASS_INFO = 4 */    
    /* ALARM_CLASS_ATTENTION = 3 */
    /* ALARM_CLASS_WARNING = 2 */
    /* ALARM_CLASS_SERIOUS = 1 */
    /* ALARM_CLASS_EMERGENCY = 0 */
	BP_UINT16 AlmClass:3;
	/* NO_CUSTOM_INFO = 0, */
	/* HAS_CUSTOM_INFO, */
    BP_UINT16 HasCustomInfo:1;
	BP_UINT16 Reserved:1;
	SigTypeU * MinVal;
	SigTypeU * MaxVal;
	SigTypeU * DefVal;
    BP_UINT8 DelayBeforeAlm;
    BP_UINT8 DelayAfterAlm;

	// /* Other info*/
	// BP_UINT16 SigSize:3;
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

typedef struct BP_SysCustomUnit {
    BP_UINT16 SigId;
    BP_UINT8 CustomType;
    void * CustomValue;
} BP_SysCustomUnit;

typedef struct BP_CusLangMap {
    BP_UINT16 SigId;
    BP_UINT16 LangId;
} BP_CusLangMap;

typedef struct BP_CusEnumLangMap {
    BP_UINT16 SigId;
    BP_UINT16 EnumVal;
    BP_UINT16 LangId;
} BP_CusEnumLangMap;

#endif

