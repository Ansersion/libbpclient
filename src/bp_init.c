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

void BP_InitPackBuf(PackBuf * pack_buf, BP_UINT8 * buf, BP_WORD buf_size)
{
    if(BP_NULL == pack_buf) {
        return;
    }
    pack_buf->Buf = buf;
    pack_buf->RmnLen = 0;
    pack_buf->PackStart = pack_buf->Buf;
    pack_buf->MsgSize = 0;
    pack_buf->BufSize = buf_size;
}

void BP_InitEmbededContext()
{
    BP_Init2Default(&BPContextEmbeded);
    BP_InitPackBuf(&PackBufEmbeded, BPBufEmbeded, BP_BUF_SIZE_EMBEDED);
    BPContextEmbeded.packBuf = &PackBufEmbeded;
    BPContextEmbeded.name = BPNameEmbeded;
    BPContextEmbeded.password = BPPasswordEmbeded;
}

void BP_Init2Default(BPContext * bp_context)
{
    if(BP_NULL == bp_context) {
        return;
    }
    bp_context->Encryption = ENCRYPTION_TYPE;;
    bp_context->CrcType = CHECKSUM_TYPE;
    bp_context->BPLevel = BP_LEVEL;
    bp_context->PerformanceLimit = PERFORMANCE_LIMIT;
    bp_context->IsDeviceClient = CLIENT_TYPE;
    bp_context->BPAlivePeroid = 60;
    bp_context->BPTimeout = 5;
    bp_context->packBuf = BP_NULL;
    bp_context->SeqIDComm = 0;
    bp_context->SeqIDPing = 0;
    bp_context->SeqIDReport = 0;
}

void BP_Init(BP_UINT8 clnt_type, BP_UINT8 cipher_type, BP_UINT16 alive_time, BP_UINT8 timeout, BP_UINT16 clnt_id)
{
	BP_ClientType = clnt_type;
	BP_CipherType = cipher_type;
	BP_AliveTime = alive_time;
	BP_Timeout = timeout;
	// BP_ClientId = clnt_id;
}
