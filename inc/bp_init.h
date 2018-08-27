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

/* default init: strong performance limit */
void BP_InitPackBuf(PackBuf * pack_buf, BP_UINT8 * buf, BP_WORD buf_size);
void BP_InitEmbededContext();
void BP_Init2Default(BPContext * bp_context);
void BP_Init(BP_UINT8 clnt_type, BP_UINT8 cipher_type, BP_UINT16 alive_time, BP_UINT8 timeout, BP_UINT16 clnt_id);
#endif

