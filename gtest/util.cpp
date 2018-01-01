//   Copyright 2017 Ansersion
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//

#include "util.h"

#define PORT 8025
#define SERVER_IP "127.0.0.1"

using namespace std;


void InitLink(int * conndfd)
{
	struct sockaddr_in serverAddr;

	if(NULL == conndfd)
	{
		ASSERT_TRUE(false);
	}
	ASSERT_NE(-1, (*conndfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)));

	memset(&serverAddr,0,sizeof(serverAddr));

	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(SERVER_IP);
	serverAddr.sin_port=htons(PORT);

	ASSERT_GE(connect(*conndfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)), 0); 


}
