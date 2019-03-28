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
/// @file 	bp_server_chain.c
/// @brief 	server chain
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_server_chain.h>
#include <bp_memset.h>
#include <bp_memcpy.h>

#ifdef DEBUG 
    #include <stdio.h>
#endif

BPServerNode BPServerChainEmbeded[BP_SERVER_CHAIN_SIZE];

/* 3 temporary server address buffer */
// BP_UINT8 ServerAddress0[BP_SERVER_ADDRESS_SIZE];
// BP_UINT8 ServerAddress1[BP_SERVER_ADDRESS_SIZE];
// BP_UINT8 ServerAddress2[BP_SERVER_ADDRESS_SIZE];


void BP_InitEmbededServerChain() {
    BP_WORD i;
    for(i = 0; i < BP_SERVER_CHAIN_SIZE; i++) {
        BPServerChainEmbeded[i].Type = BP_SERVER_TYPE_DEFAULT;
        memset_bp(BPServerChainEmbeded[i].Address, 0, BP_SERVER_ADDRESS_SIZE);
    }
}

BP_WORD UpdateUpperServerNode(BPServerNode * srv_chain, BP_WORD size, BP_WORD current_index, BPServerNode * node)
{
    BP_WORD i;
    if(BP_NULL == srv_chain || BP_NULL == node) {
        return -1;
    }
    if(0 == size) {
        return -2;
    }
    if(SRV_TYPE_INVALID(node->Type)) {
        return -3;
    }
    if(current_index > size - 1) {
        return -4;
    }
    if(BP_SERVER_TYPE_DEFAULT == node->Type) {
        /* current server node is the uppest server */
        return current_index;
    }
    if(BP_SERVER_CHAIN_SIZE - 1 == current_index) {
        /* server chain front move */
        for(i = 0; i < BP_SERVER_CHAIN_SIZE - 1; i++) {
            srv_chain[i].Type = srv_chain[i+1].Type;
            memcpy_bp(srv_chain[i].Address, srv_chain[i+1].Address, BP_SERVER_ADDRESS_SIZE);
        }
        current_index -= 1;
    }
    srv_chain[current_index + 1].Type = node->Type;
    memcpy_bp(srv_chain[current_index + 1].Address, node->Address, BP_SERVER_ADDRESS_SIZE);

    return current_index;
}

BP_WORD UpdateLowerServerNode(BPServerNode * srv_chain, BP_WORD size, BP_WORD current_index, BPServerNode * node) 
{
    BP_WORD i;
    if(BP_NULL == srv_chain || BP_NULL == node) {
        return -1;
    }
    if(0 == size) {
        return -2;
    }
    if(SRV_TYPE_INVALID(node->Type)) {
        return -3;
    }
    if(current_index > size - 1) {
        return -4;
    }
    if(BP_SERVER_TYPE_DEFAULT == node->Type) {
        /* current server node is the lowest server */
        return current_index;
    }
    if(0 == current_index) {
        /* server chain front move */
        for(i = BP_SERVER_CHAIN_SIZE - 1; i > 0; i--) {
            srv_chain[i].Type = srv_chain[i-1].Type;
            memcpy_bp(srv_chain[i].Address, srv_chain[i-1].Address, BP_SERVER_ADDRESS_SIZE);
        }
        current_index += 1;
    }
    srv_chain[current_index - 1].Type = node->Type;
    memcpy_bp(srv_chain[current_index - 1].Address, node->Address, BP_SERVER_ADDRESS_SIZE);

    return current_index;
}

void ServerNodeDump(BPServerNode * server_node)
{
#ifdef DEBUG
    BP_WORD i;
    if(BP_NULL == server_node) {
        return;
    }
    printf("%d->", server_node->Type);
    switch(server_node->Type) {
        case BP_SERVER_TYPE_IPV4: 
            {
                for(i = 0; i < 4 - 1; i++) {
                    printf("%d.", server_node->Address[i]);
                }
                printf("%d\n", server_node->Address[i]);
                break;
            }
        case BP_SERVER_TYPE_IPV6: 
            {
                for(i = 0; i < 16/2 - 1; i++) {
                    printf("%02x%02x:", server_node->Address[i*2]);
                    printf("%02x%02x:", server_node->Address[i*2+1]);
                }
                printf("%02x%02x:", server_node->Address[i*2]);
                printf("%02x%02x\n", server_node->Address[i*2+1]);
                break;
            }
        case BP_SERVER_TYPE_DOMAIN:
            {
                printf("%s\n", server_node->Address);
                break;
            }
        default:
            {
                printf("\n");
            }
    }
#endif
}
