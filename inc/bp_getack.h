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
/// @file 	bp_getack.h
/// @brief 	for BP GETACK header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_GETACK_H
#define __BP_GETACK_H

#include <bp_public.h>
#include <bp_parse.h>

// #define MAX_GET_ACK_SIG_NUM 	64

// extern BP_SigType g_SigTypeArray[MAX_GET_ACK_SIG_NUM];
// extern BP_SigId2Val g_SigArray[MAX_GET_ACK_SIG_NUM];

PackBuf * BP_PackGetack(const BPContext * bp_context, BP_GetStr * get_str);

#endif

