///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017-2019 Ansersion
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
/// @file 	bp_crc16.h
/// @brief 	functions for CRC16
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_CRC16_H
#define __BP_CRC16_H

#include <bpclient_config.h>

#ifdef CHECKSUM_CRC16
EXPORT_API BP_UINT16 BP_calc_crc16(BP_UINT8 *p, BP_WORD len);
#endif

#endif

