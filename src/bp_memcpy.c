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
/// @file 	bp_memcpy.c
/// @brief 	function "bp_memcpy" source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_memcpy.h>
// #include <stdio.h>

void * memcpy_bp(void * dst, const void * src, BP_WORD count)
{
	BP_WORD nword, npad;
	BP_WORD *s, *d;
	BP_UINT8 *s8, *d8;

	if (dst == BP_NULL || src == BP_NULL)  {
		return BP_NULL;  
	}

	if(dst == src) {
		return dst;
	}
    if(0 == count) {
        return dst;
    }

	nword = count/sizeof(dst);
	npad = count%sizeof(dst);

	s = (BP_WORD *)src;  
	d = (BP_WORD *)dst;  

	while(nword--)  
	{
		*d++ = *s++;  
		// printf("%x ", *(d-1));
	}
	// printf("\n");

	s8 = (BP_UINT8 *)s;
	d8 = (BP_UINT8 *)d;
	while(npad--)  
	{
		*d8++ = *s8++;  
		// printf("%x ", *(d8-1));
	}
	// printf("\n");

	return dst;  
}
