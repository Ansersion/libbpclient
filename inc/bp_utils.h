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
/// @file 	bp_utils.h
/// @brief 	utility functions
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_UTILS_H
#define __BP_UTILS_H

#include <bpclient_config.h>

typedef BP_WORD (*CompClbkP)(void * a,void * b); 
void SwapP(void * A[], BP_WORD i, BP_WORD j);
void BubbleSortP(void * A[], BP_WORD n, CompClbkP clbk);

#endif
