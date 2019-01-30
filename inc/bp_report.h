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

/** 
  * @Brief BP_PackReportSigTabChksum construct BPPacket REPORT that report signal table checksum
  * @Param bp_context   BP context that to update sequence ID
  * @return Success     PackBuf with packet BP REPORT
  *         Failed      BP_NULL
 */
EXPORT_API PackBuf * BP_PackReportSigTabChksum(BPContext * bp_context);

/** 
  * @Brief BP_PackReportSigTable construct BPPacket REPORT that report signal table
  * @Param bp_context   BP context that to update sequence ID
  * @return Success     PackBuf with packet BP REPORT
  *         Failed      BP_NULL
 */
EXPORT_API PackBuf * BP_PackReportSigTable(BPContext * bp_context);
EXPORT_API PackBuf * BP_PackReportSigVal(BPContext *bp_context, const BP_SigId2Val * sig_array, const BP_UINT16 sig_num);

/** 
  * @Brief BP_PackReport1SigVal construct BPPacket REPORT that report 1 signal value
  * @Param bp_context   BP context that to update sequence ID
  * @Param sig_id_2_val   the signal and its value info
  * @return Success     PackBuf with packet BP REPORT
  *         Failed      BP_NULL
 */
EXPORT_API PackBuf * BP_PackReport1SigVal(BPContext *bp_context, const BP_SigId2Val * sig_id_2_val);
#endif

