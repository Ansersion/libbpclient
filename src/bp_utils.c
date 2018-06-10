///////////////////////////////////////////////////////////////////////////////
/// Copyright 2018 Ansersion
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
/// @file 	bp_utils.c
/// @brief 	utility functions
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bp_utils.h>

void SwapP(void * A[], BP_WORD i, BP_WORD j)
{
	void * temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void BubbleSortP(void * A[], BP_WORD n, CompClbkP clbk)
{
	BP_WORD i, j;
	if(BP_NULL == A || BP_NULL == clbk) {
		return;
	}

	for (j = 0; j < n - 1; j++) {
		for (i = 0; i < n - 1 - j; i++) {
			if (clbk(A[i], A[i + 1])) {
				SwapP(A, i, i + 1);
			}
		}
	}
}

