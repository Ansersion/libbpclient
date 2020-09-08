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
/// @file 	bp_init.c
/// @brief 	initialization functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_init.h>
#include <bp_sig_table.h>
#include <bp_server_chain.h>

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
    BP_InitEmbededServerChain();
    BPContextEmbeded.ServerChain = BPServerChainEmbeded;
    BPContextEmbeded.ServerChainSize = BP_SERVER_CHAIN_SIZE;
    BPContextEmbeded.CurrentServerNodeIndex = 0;
    BPContextEmbeded.SysSigTableVersion = SYS_SIG_TABLE_VERSION;
}

void BP_Init2Default(BPContext * bp_context)
{
    // if(BP_NULL == bp_context) {
    //     return;
    // }
    // bp_context->Encryption = ENCRYPTION_TYPE;;
    // bp_context->CrcType = CHECKSUM_TYPE;
    // bp_context->BPLevel = BP_LEVEL;
    // bp_context->PerformanceLimit = PERFORMANCE_LIMIT;
    // bp_context->IsDeviceClient = CLIENT_TYPE;
    // bp_context->BPAlivePeroid = BP_ALIVE_PERIOD;
    // bp_context->BPTimeout = BP_TIMEOUT;
    // bp_context->packBuf = BP_NULL;
    // bp_context->SeqIDComm = 0;
    // bp_context->SeqIDPing = 0;
    // bp_context->SeqIDReport = 0;
    BP_Init(bp_context, ENCRYPTION_TYPE, CHECKSUM_TYPE, BP_LEVEL, PERFORMANCE_LIMIT, CLIENT_TYPE, BP_ALIVE_PERIOD, BP_TIMEOUT);
}

void BP_Init(BPContext * bp_context, BP_UINT8 cryp_type, BP_UINT8 crc_type, BP_UINT8 bplvl, BP_UINT8 perm_lmt, BP_UINT8 client_type, BP_UINT16 alive_period, BP_UINT16 timeout)
{
    if(BP_NULL == bp_context) {
        return;
    }
    bp_context->Encryption = cryp_type;;
    bp_context->CrcType = crc_type;
    bp_context->BPLevel = bplvl;
    bp_context->PerformanceLimit = perm_lmt;
    bp_context->ClientType = client_type;
    bp_context->BPAlivePeroid = alive_period;
    bp_context->BPTimeout = timeout;
    bp_context->packBuf = BP_NULL;
    bp_context->SeqIDComm = PACK_SEQ_MIN;
    bp_context->SeqIDPing = PACK_SEQ_MIN;
    bp_context->SeqIDReport = PACK_SEQ_MIN;
    bp_context->AdminNameLen = PACK_SEQ_MIN;
    bp_context->AdminName = BP_NULL;
}
