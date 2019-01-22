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
/// @file 	bp_init.h
/// @brief 	initialization functions header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_INIT_H
#define __BP_INIT_H

#include <bp_public.h>

/** 
  * @Brief: BP_InitPackBuf initialize the buffer and its parameters for communication
 */
EXPORT_API void BP_InitPackBuf(PackBuf * pack_buf, BP_UINT8 * buf, BP_WORD buf_size);

/** 
  * @Brief: BP_InitEmbededContext initialize the global variable "BPContextEmbeded" for the default(embeded) configure of BP context. 
  *         Include SN(SerialNumber), password, buffer for communication and some BP parameters.
  *         Some of them can be customized in "bpclient_config.h" and "bp_public.h" before compiling,
  *         the other can be customized in your code after compiling.
  *         You could also define your own configure by define a new BPContext.
 */
EXPORT_API void BP_InitEmbededContext();

/** 
  * @Brief: BP_Init2Default configure the parameters in "bpclient_config.h" to BPContext
  * @See: BP_Init
 */
EXPORT_API void BP_Init2Default(BPContext * bp_context);

/** 
  * @Brief: BP_Init configure the parameters for BPContext
 */
// EXPORT_API void BP_Init(BP_UINT8 clnt_type, BP_UINT8 cipher_type, BP_UINT16 alive_time, BP_UINT8 timeout, BP_UINT16 clnt_id);
EXPORT_API void BP_Init(BPContext * bp_context, BP_UINT8 cryp_type, BP_UINT8 crc_type, BP_UINT8 bplvl, BP_UINT8 perm_lmt, BP_UINT8 client_type, BP_UINT16 alive_period, BP_UINT16 timeout);
#endif

