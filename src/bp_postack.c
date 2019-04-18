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
/// @file 	bp_postack.c
/// @brief 	for BP POSTACK functions source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>
#include <bp_sig_table_tools.h>
#include <bp_postack.h>
#include <bp_sig_table.h>

// #include <stdio.h>
// #include <string.h>

// PackBuf * BP_PackGetack(BP_UINT16 seq_id, BP_UINT8 ret_code, BP_UINT16 * sig_index_array, BP_UINT16 array_num)
PackBuf * BP_PackPostack(const BPContext * bp_context, BP_PostackStr * postack_str)
{
#ifdef DEBUG
	BP_WORD i;
#endif

	BP_UINT8 * pbuf, * pbuf_old;
	BP_WORD rmn_len = 0;

	BPPackVrbHead vrb_head;
	BPPackPayload payload;

    if(BP_NULL == bp_context) {
        return BP_NULL;
    }
    if(BP_NULL == bp_context->packBuf) {
        return BP_NULL;
    }

	if(BP_NULL == postack_str) {
		return BP_NULL;
	}

	BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_POSTACK_MSK);
	pbuf = bp_context->packBuf->PackStart;
	pbuf_old = pbuf;

	vrb_head.u.POSTACK.Flags = postack_str->Flags;
	vrb_head.u.POSTACK.SeqId = postack_str->SeqId;
	vrb_head.u.POSTACK.RetCode = postack_str->RetCode;

	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_POSTACK);

    /* TODO: set signal id when ret_code != 0*/
    // payload.u.GETACK.SigTypeArray = g_SigTypeArray;
    // payload.u.GETACK.SigArray = g_SigArray;
    pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_POSTACK, &vrb_head);

	// set remaining length and pack the packet
	rmn_len = (BP_WORD)(pbuf-pbuf_old);
	bp_context->packBuf->RmnLen = rmn_len;
	pbuf = BP_ToPack(bp_context->packBuf);

#ifdef DEBUG
    printf("postack debug:\n");
	for(i = 0; i < bp_context->packBuf->MsgSize; i++) {
		printf("%02x ", pbuf[i]);
	}
	printf("\n");
#endif

	return bp_context->packBuf;
}

