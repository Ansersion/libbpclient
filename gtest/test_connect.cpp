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

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <gtest/gtest.h>

extern "C" 
{
#include <bp_connect.h>
#include <bpclient_config.h>
#include <bp_public.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_parse.h>
#include <bp_crc32.h>
#include <bp_init.h>
}

#define PORT 8025
#define SERVER_IP "127.0.0.1"

using namespace std;


	int conndfd;
	struct sockaddr_in serverAddr;
	int n;
	int len;

	BP_UINT8 * user_name = (BP_UINT8 *)"3";
	BP_UINT8 * correct_password = (BP_UINT8 *)"123456abcdefghijklmnopqrstuvwxyz";
	BP_UINT8 * wrong_password = (BP_UINT8 *)"123456";

	BP_UINT8 buf[2048+1];
	BP_UINT16 left_len;
	BP_UINT8 type_and_flags;

	PackBuf * p_pack_buf;
	BP_ConnackStr str_connack;

	void InitLink()
	{
		conndfd = 0;
		n = 0;
		len = 0;
		left_len = 0;
		type_and_flags = 0;
		p_pack_buf = 0;
		memset(buf, 0, sizeof(buf));
		ASSERT_NE(-1, (conndfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)));

		memset(&serverAddr,0,sizeof(serverAddr));

		serverAddr.sin_family=AF_INET;
		serverAddr.sin_addr.s_addr=inet_addr(SERVER_IP);
		serverAddr.sin_port=htons(PORT);

		ASSERT_GE(connect(conndfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)), 0); 

		BP_Init2Default();

	}



TEST(CONNECT_OK, USR_NAME_PWD_OK)
{
	InitLink();
	p_pack_buf = BP_PackConnect(user_name, correct_password);
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);

	ASSERT_EQ(n, p_pack_buf->MsgSize);

	n=recv(conndfd,buf,MAX_FIX_HEAD_SIZE, MSG_WAITALL);
	BP_ParseFixHead(buf, &type_and_flags, &left_len);
	len = left_len;
	n += recv(conndfd,buf+MAX_FIX_HEAD_SIZE,len, MSG_WAITALL);
	len += MAX_FIX_HEAD_SIZE;

	ASSERT_EQ(n, len);
	ASSERT_EQ(0, BP_CheckCRC(type_and_flags, buf, len));

	BP_ParseConnack(&str_connack, buf, len);

	EXPECT_EQ(RET_CODE_CONNACK_OK, str_connack.RetCode);

	close(conndfd);
}

TEST(CONNECT_ERR, PASSWORD_ERR)
{
	InitLink();
	p_pack_buf = BP_PackConnect(user_name, wrong_password);
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);

	ASSERT_EQ(n, p_pack_buf->MsgSize);

	n=recv(conndfd,buf,MAX_FIX_HEAD_SIZE, MSG_WAITALL);
	BP_ParseFixHead(buf, &type_and_flags, &left_len);
	len = left_len;
	n += recv(conndfd,buf+MAX_FIX_HEAD_SIZE,len, MSG_WAITALL);
	len += MAX_FIX_HEAD_SIZE;

	ASSERT_EQ(n, len);
	ASSERT_EQ(0, BP_CheckCRC(type_and_flags, buf, len));

	BP_ParseConnack(&str_connack, buf, len);

	EXPECT_EQ(RET_CODE_CONNACK_PWD_INVALID, str_connack.RetCode);

	close(conndfd);
}
