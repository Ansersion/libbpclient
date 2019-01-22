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
/// @file 	bp_crc32.h
/// @brief 	functions for CRC32
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_CRC32_H
#define __BP_CRC32_H

#include <bpclient_config.h>

#ifdef CHECKSUM_CRC32
EXPORT_API BP_UINT32 BP_calc_crc32(BP_UINT8 *p, BP_WORD bytelength);
#endif

#endif

