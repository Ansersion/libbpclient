///////////////////////////////////////////////////////////////////////////////
/// Copyright 2018 Ansersion
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
/// @file 	bp_sig_table_tools.h
/// @brief 	
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////
#ifndef __BP_SIG_TABLE_TOOLS_H
#define __BP_SIG_TABLE_TOOLS_H

#include <bp_sig_str.h>

#define SYSTEM_SIGNAL_ID_START      0xE000
#define SYSTEM_SIGNAL_ID_DIST_NUM   0x200
#define MAX_SYS_SIG_DIST_NUM 	16
#define MAX_STRING_SIG_VAL_LEN 	255

extern const BP_UINT8 STRING_NONE[];
extern const SigTypeU STRING_DEFAULT_VALUE;

BP_UINT16 BP_GetSigIdx(const BP_UINT16 sig_id);
BP_SigId2Val * BP_GetSigId2Val(const BP_UINT16 sig_idx, const BP_UINT16 sig_id);
BP_UINT16 BP_GetSigType(const BP_UINT16 sig_id);
BP_INT16 BP_SetSigVal(BP_UINT8 sig_num, BP_SigId2Val * sig_array);
void BP_SigDump(void);
BP_UINT32 BP_GetSigTabChk();
BP_UINT8 * BP_SetSigVal2Buf(BP_UINT8 * buf, const BP_SigId2Val * sig_id_2_val);
BP_UINT8 * BP_SetSigVal2Buf2(BP_UINT8 * buf, BP_SigType sig_type, SigTypeU sig_val);

BP_UINT8 whichDist(BP_UINT16 sys_sig_id);
BP_UINT8 hasMinMax(BP_UINT16 sig_type);

#endif

