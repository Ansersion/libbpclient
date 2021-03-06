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
/// @file 	bp_specack.c
/// @brief 	for BP SPECACK functions source file
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
#include <bp_specack.h>
#include <bp_sig_table.h>

#ifdef DEBUG
    #include <stdio.h>
#endif
// #include <string.h>

PackBuf * BP_PackSpecack(BPContext * bp_context, BP_SpecackStr * specack_str)
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

	if(BP_NULL == specack_str) {
		return BP_NULL;
	}

	if(BP_NULL == BP_InitPack(bp_context->packBuf, BP_PACK_TYPE_SPECACK_MSK)) {
#ifdef DEBUG
        printf("BP_InitPack failed\n");
#endif
        return BP_NULL;
    }
	pbuf = bp_context->packBuf->PackStart;
	pbuf_old = pbuf;

	vrb_head.u.SPECACK.Type = specack_str->Type;
	vrb_head.u.SPECACK.RetCode = specack_str->RetCode;
	// vrb_head.u.SPECACK.SeqId = (bp_context->SeqIDComm)++;
    SET_PACK_SEQ(vrb_head.u.SPECACK.SeqId, bp_context->SeqIDComm);

	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_SPECACK);

    pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_SPECACK, &vrb_head);

	// set remaining length and pack the packet
	rmn_len = (BP_WORD)(pbuf-pbuf_old);
	bp_context->packBuf->RmnLen = rmn_len;
	pbuf = BP_ToPack(bp_context->packBuf);

#ifdef DEBUG
    printf("specack_str debug2:\n");
	for(i = 0; i < bp_context->packBuf->MsgSize; i++) {
		printf("%02x ", bp_context->packBuf->PackStart[i]);
	}
	printf("\n");
    printf("packBuf addr: %p\n", bp_context->packBuf);
#endif

	return bp_context->packBuf;
}

