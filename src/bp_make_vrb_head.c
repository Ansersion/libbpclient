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
/// @file 	bp_make_vrb_head.c
/// @brief 	functions to make variable header for BP packet source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_make_vrb_head.h>
#include <bp_public.h>
#include <bp_pack_type.h>

BP_UINT8 * make_vrb_cnct(BP_UINT8 * pack, BPPackVrbHead * vrb_head);
BP_UINT8 * make_vrb_discnct(BP_UINT8 * pack, BPPackVrbHead * vrb_head);

BP_UINT8 * BP_make_vrb_head(BP_UINT8 * pack, BPPackVrbHead * vrb_head, BP_UINT8 bp_type)
{
	if(BP_NULL == pack) {
		return BP_NULL;
	}

	if(BP_NULL == vrb_head) {
		return BP_NULL;
	}

	switch(bp_type) {
		case BP_PACK_TYPE_CONNECT: 	
			pack = make_vrb_cnct(pack, vrb_head);
			break;
		case BP_PACK_TYPE_CONNACK: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_GET: 		
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_GETACK: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_POST: 		
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_POSTACK: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_REPORT: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_RPRTACK: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PING: 		
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PINGACK: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PUSH:
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PUSHACK:
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_DISCONN:
			pack = make_vrb_discnct(pack, vrb_head);
			break;
		default:
			printf("Err: unsupported BP type: %d\n", bp_type);
			break;
	}

	return pack;
}

BP_UINT8 * make_vrb_cnct(BP_UINT8 * pack, BPPackVrbHead * vrb_head)
{
	*pack++ = vrb_head->u.CONNECT.Level;
	*pack++ = vrb_head->u.CONNECT.Flags;
	pack = BP_SetBig16(pack, vrb_head->u.CONNECT.ClntId);
	pack = BP_SetBig16(pack, vrb_head->u.CONNECT.AlvTime);
	*pack++ = vrb_head->u.CONNECT.Timeout;
	return pack;
}

BP_UINT8 * make_vrb_discnct(BP_UINT8 * pack, BPPackVrbHead * vrb_head)
{
	pack = BP_SetBig16(pack, vrb_head->u.CONNECT.ClntId);
	return pack;
}
