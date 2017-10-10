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
/// @file 	bp_memcpy.h
/// @brief 	function "bp_memcpy" header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BP_MEMCPY_H
#define __BP_MEMCPY_H

#include <bpclient_config.h>

/** memory copy function
 *  
 * 	copy "count" bytes from "src" to "dst"  
 * 	@param dst destination address
 * 	@param src source address  
 * 	@param count size copied
 * 	@return  BP_NULL/dst BP_NULL: dst/src equals BP_NULL; dst: copy OK
 * 	@note  there will be something when the memories of dst and src are overlapped
 * 	
 */ 
void * memcpy_bp(void * dst, const void * src, BP_WORD count);

#endif
