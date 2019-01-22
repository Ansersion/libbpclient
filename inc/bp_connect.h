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
/// @file 	bp_connect.h
/// @brief 	for BP CONNECT header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_CONNECT_H
#define __BP_CONNECT_H

#include <bp_public.h>

/** 
  * @Brief BP_PackConnect construct BPPacket: CONNECT
  * @Param bp_context   BP context that to update SN and password
  * @Param sn   Serial Number of device client, which will be copied into context
  * @Param password     Password that will be copied into context
  * @return Success     PackBuf with packet BP CONNECT
  *         Failed      BP_NULL
 */
EXPORT_API PackBuf * BP_PackConnect(const BPContext * bp_context, BP_UINT8 * sn, BP_UINT8 * password);
#endif

