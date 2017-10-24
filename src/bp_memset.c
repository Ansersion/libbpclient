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
/// @file 	bp_memset.c
/// @brief 	function "bp_memset" source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// @see Thinks: http://blog.csdn.net/u011118276/article/details/46742341
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_memset.h>

void * memset_bp(void *s, BP_UINT8 c, BP_WORD n)  
{  
	if (BP_NULL == s)
		return BP_NULL;  
	BP_UINT8 * tmpS = (BP_UINT8 *)s;  
	while(n-- > 0)  
		*tmpS++ = c;  
	return s;   
}  
