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

extern "C"
{
#include <bpclient_config.h>
#include <bp_public.h>
// #include <bp_make_fix_head.h>
// #include <bp_make_vrb_head.h>
// #include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>
#include <bp_init.h>
#include <bp_connect.h>
#include <bp_disconn.h>
#include <bp_parse.h>
#include <bp_sys_sig.h>
#include <bp_report.h>
#include <bp_getack.h>
#include <bp_postack.h>
#include <bp_ping.h>
#include <bp_pingack.h>
#include <bp_sig_table.h>
}


/*****************************
 * Test Case ID: 0001
 * Test Case Number: 1.3.2
 * Author: 	Ansersion
 * Date: 	2018-01-01
 * Description:
 * 	Test the PING packet if some inputs are with errors
*/

TEST(PING_ERR, PING_CLNT_ID_ERR)
{
	int n = 0;
	int len = 0;
	int conndfd;
	BP_UINT16 alive_time = 10;
	BP_UINT16 timeout = 5;
	BP_UINT8 buf[2048+1];
	BP_UINT16 left_len;
	BP_UINT8 type_and_flags;
	BP_UINT8 * user_name = (BP_UINT8 *)"3";
	BP_UINT8 * correct_password = (BP_UINT8 *)"123456abcdefghijklmnopqrstuvwxyz";
	BP_UINT16 unknown_clnt_id = 1111;

	PackBuf * p_pack_buf;
	BP_ConnackStr str_connack;
	BP_PingackStr str_pingack;


	memset(buf, 0, sizeof(buf));

	InitLink(&conndfd);

	BP_Init(0, 0, alive_time, timeout, BP_CLIENT_ID_APPLY);
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

	ASSERT_EQ(RET_CODE_CONNACK_OK, str_connack.RetCode);

	// BP_ClientId = unknown_clnt_id;

	p_pack_buf = BP_PackPing();
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
	ASSERT_EQ(n, p_pack_buf->MsgSize);

	n=recv(conndfd,buf,MAX_FIX_HEAD_SIZE, MSG_WAITALL);
	BP_ParseFixHead(buf, &type_and_flags, &left_len);
	len = left_len;
	n += recv(conndfd,buf+MAX_FIX_HEAD_SIZE,len, MSG_WAITALL);
	len += MAX_FIX_HEAD_SIZE;

	ASSERT_EQ(n, len);
	ASSERT_EQ(0, BP_CheckCRC(type_and_flags, buf, len));

	BP_ParsePingack(&str_pingack, buf, len);

	EXPECT_EQ(RET_CODE_PINGACK_CLNT_ID_INVALID, str_pingack.RetCode);

	close(conndfd);
}

TEST(PING_ERR, PING_OVER_ALIVE_TIME_ERR)
{
	int n = 0;
	int len = 0;
	int conndfd;
	BP_UINT16 alive_time = 10;
	BP_UINT16 timeout = 5;
	BP_UINT8 buf[2048+1];
	BP_UINT16 left_len;
	BP_UINT8 type_and_flags;
	BP_UINT8 * user_name = (BP_UINT8 *)"3";
	BP_UINT8 * correct_password = (BP_UINT8 *)"123456abcdefghijklmnopqrstuvwxyz";

	PackBuf * p_pack_buf;
	BP_ConnackStr str_connack;
	BP_PingackStr str_pingack;


	memset(buf, 0, sizeof(buf));

	InitLink(&conndfd);

	BP_Init(0, 0, alive_time, timeout, BP_CLIENT_ID_APPLY);

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

	ASSERT_EQ(RET_CODE_CONNACK_OK, str_connack.RetCode);

	sleep(alive_time - 1);
	
	p_pack_buf = BP_PackPing();
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
	ASSERT_EQ(n, p_pack_buf->MsgSize);

	n=recv(conndfd,buf,MAX_FIX_HEAD_SIZE, MSG_WAITALL);
	BP_ParseFixHead(buf, &type_and_flags, &left_len);
	len = left_len;
	n += recv(conndfd,buf+MAX_FIX_HEAD_SIZE,len, MSG_WAITALL);
	len += MAX_FIX_HEAD_SIZE;

	ASSERT_EQ(n, len);
	ASSERT_EQ(0, BP_CheckCRC(type_and_flags, buf, len));

	BP_ParsePingack(&str_pingack, buf, len);

	EXPECT_EQ(RET_CODE_PINGACK_OK, str_pingack.RetCode);

	sleep(alive_time + 1);
	p_pack_buf = BP_PackPing();
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
	ASSERT_EQ(n, p_pack_buf->MsgSize);
	n=recv(conndfd,buf,MAX_FIX_HEAD_SIZE, MSG_WAITALL);
	EXPECT_LE(n, 0);

	close(conndfd);
}
