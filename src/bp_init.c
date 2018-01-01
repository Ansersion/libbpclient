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
/// @file 	bp_init.c
/// @brief 	initialization functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_init.h>

void BP_Init2Default()
{
	BP_ClientType = 0;
	BP_CipherType = 0;
	BP_AliveTime = 60;
	BP_Timeout = 5;
	BP_ClientId = BP_CLIENT_ID_APPLY;
}

void BP_Init(BP_UINT8 clnt_type, BP_UINT8 cipher_type, BP_UINT16 alive_time, BP_UINT8 timeout, BP_UINT16 clnt_id)
{
	BP_ClientType = clnt_type;
	BP_CipherType = cipher_type;
	BP_AliveTime = alive_time;
	BP_Timeout = timeout;
	BP_ClientId = clnt_id;
}
