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

#define PORT 8025
#define SERVER_IP "127.0.0.1"
int main()
{
	int conndfd;
	struct sockaddr_in serverAddr;
	int n;
	int len;
	int loop = 1;
	char input[128];

	fd_set rfds;
	struct timeval tv;
	int retval;

	BP_UINT8 * user_name = "Ansersion4";
	BP_UINT8 * password = "ansersion4";

	BP_UINT8 buf[2048+1];
	BP_UINT16 left_len;
	BP_UINT32 crc = 0;
	BP_UINT8 type_and_flags;

	PackBuf pack_buf;
	PackBuf * p_pack_buf;
	BP_ConnackStr str_connack;

	if(-1==(conndfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))) {
		printf("Create Socket Error\n");
	}

	memset(&serverAddr,0,sizeof(serverAddr));

	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(SERVER_IP);
	serverAddr.sin_port=htons(PORT);

	if(connect(conndfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0) {
		printf("Connect Error\n");
		exit(0);
	}

	BP_Init2Default();

	loop = 1;

	while(loop) {
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		FD_SET(conndfd, &rfds);
		tv.tv_sec = 120;
		tv.tv_usec = 0;
		retval = select(conndfd+1, &rfds, NULL, NULL, &tv);
		if(-1 == retval) {
			perror("select()");
			loop = 0;
		} else if(0 == retval) {
			printf("timeout 120 seconds\n");
		} else {
			if(FD_ISSET(0, &rfds)) {
				if(NULL == fgets(input, sizeof(input), stdin)) {
					printf("fgets error\n");
					exit(1);
				}
				if(strncmp(input, "p", 1) == 0) {
					printf("cmd: p\n");
				} else if(strncmp(input, "r", 1) == 0){
					p_pack_buf = BP_PackReport(BP_NULL, g_SysSigMap);
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
						close(conndfd);
						perror("Send error");
						return -1;
					}
					printf("report\n");
				} else if(strncmp(input, "i", 1) == 0) {
					printf("cmd: i\n");
				} else if(strncmp(input, "c", 1) == 0) {
					p_pack_buf = BP_PackConnect(user_name, password);
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
						close(conndfd);
						perror("Send error");
						return -1;
					}
					printf("connect\n");
				} else if(strncmp(input, "d", 1) == 0) {
					p_pack_buf = BP_PackDisconn();
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
						close(conndfd);
						perror("Send error");
						return -3;
					}
					printf("disconn\n");
					loop = 0;
				} else {
					printf("not supported input\n");
				}
			}
			if(FD_ISSET(conndfd, &rfds)) {
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
					continue;
				}
				switch((type_and_flags >> 4) & 0x0F) {
					case BP_PACK_TYPE_CONNACK:
						BP_ParseConnack(&str_connack, buf, len);
						printf("client id = %d\n", str_connack.ClientID);
						printf("system signal set version = %d\n", str_connack.SysSigSetVersion);
						break;
					default:
						printf("recv pack unknown\n");
				}
			}
		}
	}

	close(conndfd);
	return 0;
}
