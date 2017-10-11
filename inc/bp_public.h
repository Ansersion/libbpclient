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
/// @file 	bp_public.h
/// @brief 	public tool functions header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_PUBLIC_H
#define __BP_PUBLIC_H

#include <bpclient_config.h>

#define BP_LEVEL 	0
#define BP_CLIENT_ID_LEN 	2

#define BP_SetBig16 	BP_SetNet16
#define BP_SetBig32 	BP_SetNet32

BP_UINT8 * BP_SetNet16(BP_UINT8 * dst, BP_UINT16 val);
BP_UINT8 * BP_SetNet32(BP_UINT8 * dst, BP_UINT32 val);

BP_UINT8 * BP_Set2ByteField(BP_UINT8 * pack, BP_UINT8 * field, BP_UINT16 field_len);


#endif

