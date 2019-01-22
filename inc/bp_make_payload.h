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
/// @file 	bp_make_payload.h
/// @brief 	functions to make payload for BP packet header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_MAKE_PAYLOAD_HEAD_H
#define __BP_MAKE_PAYLOAD_HEAD_H

#include <bpclient_config.h>
#include <bp_public.h>

extern BP_SigType g_SigTypeArray[];
extern BP_SigId2Val g_SigArray[];
extern BP_SigValArrayEntry g_SigValArray[];

/** 
  * @Brief BP_make_payload construct payload for BP packet
  * @Param pack       packet buffer
  * @Param vrb_head   payload info
  * @Param bp_type    BP packet type
  * @Param vrb_head   variable head info
  * @return Success   Pointer to the end of the payload info of parameter "pack"
  *         Failed      BP_NULL
 */
BP_UINT8 * BP_make_payload(BP_UINT8 * pack, BPPackPayload * payload, BP_UINT8 bp_type, BPPackVrbHead * vrb_head);


#endif

