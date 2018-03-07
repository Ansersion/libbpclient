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
#include <bp_sig_table.h>


#define PORT 8025
#define SERVER_IP "127.0.0.1"

BP_UINT8 DEV_NAME[] = "AnsersionDev";

int main(int argc, char* argv[])
{

	int conndfd;
	struct sockaddr_in serverAddr;
	int n;
	int len;
	int loop = 1;
	int i;
	char input[128];

	fd_set rfds;
	struct timeval tv;
	int retval;

	BP_UINT8 * user_name = "3";
	BP_UINT8 * password = "123456abcdefghijklmnopqrstuvwxyz";

	BP_UINT8 buf[2048+1];
	BP_UINT16 left_len;
	BP_UINT32 crc = 0;
	BP_UINT8 type_and_flags;

	PackBuf pack_buf;
	PackBuf * p_pack_buf;
	BP_ConnackStr str_connack;
	BP_PingackStr str_pingack;
	BP_GetStr str_get;
	BP_PostStr str_post;

	if(argc != 2) {
		printf("usage: %s <IP>\n", argv[0]);
		exit(-1);
	}

	if(-1==(conndfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))) {
		printf("Create Socket Error\n");
	}

	printf("start connect %s\n", argv[1]);

	memset(&serverAddr,0,sizeof(serverAddr));

	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
	serverAddr.sin_port=htons(PORT);

	if(connect(conndfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0) {
		printf("Connect Error\n");
		exit(0);
	}

	BP_Init2Default();

	p_pack_buf = BP_PackConnect(user_name, password);

	printf("start connecting\n");
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
	if(n != p_pack_buf->MsgSize) {
		close(conndfd);
		perror("Send error");
		return -1;
	}

	n=recv(conndfd,buf,MAX_FIX_HEAD_SIZE, MSG_WAITALL);
	if(MAX_FIX_HEAD_SIZE != n) {
		close(conndfd);
		perror("Recv error 1");
		return -2;
	}
	BP_ParseFixHead(buf, &type_and_flags, &left_len);

	len = left_len;

	n += recv(conndfd,buf+MAX_FIX_HEAD_SIZE,len, MSG_WAITALL);
	len += MAX_FIX_HEAD_SIZE;

	if(n != len) {
		close(conndfd);
		printf("Recv error 2");
		return -2;
	}

	if(0 != BP_CheckCRC(type_and_flags, buf, len)) {
		printf("CRC Check error\n");
		close(conndfd);
		return -3;
	}
	if(((type_and_flags >> 4) & 0x0F) != BP_PACK_TYPE_CONNACK) {
		printf("Packet type error\n");
		close(conndfd);
		return -3;
	} 
	BP_ParseConnack(&str_connack, buf, len);
	printf("*********CONNECT OK**********\n");
	printf("CONNACK:\n");
	printf("RetCode = %d\n", str_connack.RetCode);
	printf("client id = %d\n", str_connack.ClientID);
	printf("system signal set version = %d\n", str_connack.SysSigSetVersion);

	close(conndfd);

	return 0;
}
