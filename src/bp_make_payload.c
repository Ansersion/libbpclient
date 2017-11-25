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
/// @file 	bp_make_payload.c
/// @brief 	functions to make payload for BP packet source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_make_payload.h>
#include <bp_public.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>

// std
#include <stdio.h>

BP_UINT8 * make_pld_cnct(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);
BP_UINT8 * make_pld_rprt(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head);

BP_UINT8 * BP_make_payload(BP_UINT8 * pack, BPPackPayload * payload, BP_UINT8 bp_type, BPPackVrbHead * vrb_head)
{
	if(BP_NULL == pack) {
		return BP_NULL;
	}

	if(BP_NULL == payload) {
		return BP_NULL;
	}

	switch(bp_type) {
		case BP_PACK_TYPE_CONNECT: 	
			pack = make_pld_cnct(pack, payload, vrb_head);
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
			pack = make_pld_rprt(pack, payload, vrb_head);
			break;
		case BP_PACK_TYPE_RPRTACK: 	
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PING: 		
			// No payload
			break;
		case BP_PACK_TYPE_PINGACK: 	
			// No payload
			break;
		case BP_PACK_TYPE_PUSH:
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_PUSHACK:
			printf("Err: unsupported BP type\n");
			break;
		case BP_PACK_TYPE_DISCONN:
			// No payload
			break;
		default:
			printf("Err: unsupported BP type: %d\n", bp_type);
			break;
	}

	return pack;
}

BP_UINT8 * make_pld_cnct(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	pack = BP_Set2ByteField(pack, payload->u.CONNECT.Name, payload->u.CONNECT.NameLen);
	pack = BP_Set2ByteField(pack, payload->u.CONNECT.Pwd, payload->u.CONNECT.PwdLen);
	*pack++ = payload->u.CONNECT.ClntIdLen;
	pack = BP_SetNet16(pack, payload->u.CONNECT.ClntId);
	return pack;
}

BP_UINT8 * make_pld_rprt(BP_UINT8 * pack, BPPackPayload * payload, BPPackVrbHead * vrb_head)
{
	BP_UINT16 i, j;
	const BP_UINT8 * sig_map;
	printf("make_pld_rprt: %d\n", payload->u.REPORT.SysSigMapSize);
	if(vrb_head->u.REPORT.Flags & BP_VRB_FLAG_SYS_SIG_SET_MSK) {
		*pack++ = payload->u.REPORT.DevNameLen;
		for(i = 0; i < payload->u.REPORT.DevNameLen; i++) {
			*pack++ = payload->u.REPORT.DevName[i];
		}
	}
	for(i = 0; i < payload->u.REPORT.SysSigMapSize; i++) {
		*pack++ = payload->u.REPORT.SysSigMap->Dist;
		sig_map = payload->u.REPORT.SysSigMap->SigMap;
		printf("make_pld_rprt 2: %d\n", payload->u.REPORT.SysSigMap->SigMapSize);

		for(j = 0; j < payload->u.REPORT.SysSigMap->SigMapSize; j++) {
			*pack++ = *sig_map++;
		}
	}
	return pack;
}

