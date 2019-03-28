///////////////////////////////////////////////////////////////////////////////
/// Copyright 2019 Ansersion
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
/// @file 	bp_server_chain.h
/// @brief 	server chain
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_SERVER_CHAIN_H
#define __BP_SERVER_CHAIN_H

#include <bpclient_config.h>

#define BP_SERVER_CHAIN_SIZE 	3
#define BP_SERVER_ADDRESS_SIZE 	64


#define BP_SERVER_TYPE_DEFAULT 	0
#define BP_SERVER_TYPE_IPV4 	1
#define BP_SERVER_TYPE_IPV6     2
#define BP_SERVER_TYPE_DOMAIN 	3

#define SRV_TYPE_INVALID(t) ((t) < BP_SERVER_TYPE_DEFAULT || (t) > BP_SERVER_TYPE_DOMAIN)


typedef struct BPServerNode {
    BP_UINT8 Type;
    BP_UINT8 Address[BP_SERVER_ADDRESS_SIZE];
} BPServerNode;


EXPORT_API BPServerNode BPServerChainEmbeded[BP_SERVER_CHAIN_SIZE];
// EXPORT_API BP_UINT8 ServerAddress0[BP_SERVER_ADDRESS_SIZE];
// EXPORT_API BP_UINT8 ServerAddress1[BP_SERVER_ADDRESS_SIZE];
// EXPORT_API BP_UINT8 ServerAddress2[BP_SERVER_ADDRESS_SIZE];

EXPORT_API void BP_InitEmbededServerChain();
EXPORT_API BP_WORD UpdateUpperServerNode(BPServerNode * srv_chain, BP_WORD size, BP_WORD current_index, BPServerNode * node);
EXPORT_API BP_WORD UpdateLowerServerNode(BPServerNode * srv_chain, BP_WORD size, BP_WORD current_index, BPServerNode * node); 

EXPORT_API void ServerNodeDump(BPServerNode * srv_node);



#endif
