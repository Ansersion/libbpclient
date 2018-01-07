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
/// @file 	bp_report.h
/// @brief 	for BP REPORT header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_REPORT_H
#define __BP_REPORT_H

#include <bp_public.h>

// PackBuf * BP_PackReport(BP_UINT8 * dev_name, const BP_SysSigMap * sys_sig_map);
// PackBuf * BP_PackReport(BP_UINT8 * dev_name, const BP_SysSigMap * sys_sig_map, const BP_UINT16 sys_sig_map_size);
/**************
 * Parse the REPORT packet.
 * 	@Note:
 * 		if(null == sig_array) dev_name/sys_sig_map must not be null
 * 		else dev_name & sys_sig_map must be null
***************/
PackBuf * BP_PackReport(BP_UINT8 * dev_name, const BP_SysSigMap * sys_sig_map, const BP_SigId2Val * sig_array, const BP_UINT16 num);
#endif

