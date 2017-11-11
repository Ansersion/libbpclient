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
#include <bp_make_fix_head.h>
#include <bp_make_vrb_head.h>
#include <bp_make_payload.h>
#include <bp_make_pack.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>
#include <bp_init.h>
#include <bp_connect.h>
#include <bp_disconn.h>

#define PORT 8025
#define SERVER_IP "127.0.0.1"
int main()
{
	int conndfd;
	struct sockaddr_in serverAddr;
	int n;
	int len;
	int i;
	int multiplier;
	int loop = 1;
	char input[128];

	fd_set rfds;
	struct timeval tv;
	int retval;

	BP_UINT8 * user_name = "Ansersion4";
	BP_UINT8 * password = "ansersion4";

	BP_UINT8 buf[2048+1];
	BP_UINT8 * pbuf = buf, * pbuf_old;
	BP_UINT16 client_id = 0;
	BP_UINT16 alive_time = 0x000f;
	BP_UINT8 timeout = 0xC;
	BP_WORD rmn_len = 0;
	BP_UINT32 crc = 0;

	PackBuf pack_buf;
	PackBuf * p_pack_buf;

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

	/*
	BP_InitPack(&pack_buf, BP_PACK_TYPE_CONNECT_MSK, pbuf, 2048);

	pbuf = pack_buf.PackStart;
	pbuf_old = pbuf;

	*/
	// variable header
	BPPackVrbHead vrb_head;
	vrb_head.u.CONNECT.Level = BP_LEVEL;
	vrb_head.u.CONNECT.Flags = BP_VRB_FLAG_USER_NAME_MSK | BP_VRB_FLAG_PASSWORD_MSK | BP_VRB_FLAG_DEV_CLNT_MSK;
	vrb_head.u.CONNECT.ClntId = client_id;
	vrb_head.u.CONNECT.AlvTime = alive_time;
	vrb_head.u.CONNECT.Timeout = timeout;
	pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_CONNECT);

	// payload
	BPPackPayload payload;
	payload.u.CONNECT.NameLen = strlen(user_name);
	payload.u.CONNECT.Name = user_name;
	payload.u.CONNECT.PwdLen = strlen(password);
	payload.u.CONNECT.Pwd = password;
	payload.u.CONNECT.ClntIdLen = BP_CLIENT_ID_LEN;
	payload.u.CONNECT.ClntId = BP_CLIENT_ID_APPLY;
	pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_CONNECT);

	/*
	// set remaining length and pack the packet
	rmn_len = (BP_WORD)(pbuf-pbuf_old);
	pack_buf.RmnLen = rmn_len;
	pbuf = BP_ToPack(&pack_buf);

	for(i = 0; i < pack_buf.MsgSize; i++) {
		printf("%02x ", pbuf[i]);
	}
	printf("\n");
	*/

	p_pack_buf = BP_PackConnect(user_name, password);

	// n=send(conndfd,pbuf,pack_buf.MsgSize,0);
	n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
	if(n != p_pack_buf->MsgSize) {
		close(conndfd);
		perror("Send error");
		return -1;
	}

	n=recv(conndfd,buf,3, MSG_WAITALL);
	if(3 != n) {
		close(conndfd);
		perror("Recv error 1");
		return -2;
	}
	multiplier = 1;
	i = 0;
	len = 0;
	do {
		i++;
		len += (buf[i] & 0x7F) * multiplier;
		multiplier *= 128;
		if(multiplier > 128) {
			close(conndfd);
			printf("parse remaining length error");
			return -3;
		}
	} while((buf[i] & 0x80) != 0);

	if(len < 128) len--;

	n += recv(conndfd,buf+3,len, MSG_WAITALL);

	crc = BP_calc_crc32(buf, len+3-4);
	printf("len+3-4=%d, crc=%x\n", len+3-4, crc);

	if(n != len + 3) {
		close(conndfd);
		printf("Recv error 2");
		return -2;
	}
	printf("recv %d bytes\n", n);
	for(i = 0; i < n; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");

	BP_GetBig16(buf + 6, &client_id);
	printf("client id = %d\n", client_id);

	BP_Client_Id = client_id;

	p_pack_buf = BP_PackDisconn();

	// BP_ReinitPack(&pack_buf, BP_PACK_TYPE_DISCONN_MSK);

	// pbuf = pack_buf.PackStart;
	// pbuf_old = pbuf;

	// // variable header
	// vrb_head.u.DISCONN.ClntId = client_id;
	// pbuf = BP_make_vrb_head(pbuf, &vrb_head, BP_PACK_TYPE_DISCONN);

	// // payload
	// pbuf = BP_make_payload(pbuf, &payload, BP_PACK_TYPE_DISCONN);

	// // set remaining length and pack the packet
	// rmn_len = (BP_WORD)(pbuf-pbuf_old);
	// pack_buf.RmnLen = rmn_len;
	// pbuf = BP_ToPack(&pack_buf);

	// for(i = 0; i < pack_buf.MsgSize; i++) {
	// 	printf("%02x ", pbuf[i]);
	// }
	// printf("\n");

	n=send(conndfd,pbuf,pack_buf.MsgSize,0);
	if(n != pack_buf.MsgSize) {
		close(conndfd);
		perror("Send error");
		return -3;
	}

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
					printf("cmd: r\n");
				} else if(strncmp(input, "i", 1) == 0) {
					printf("cmd: i\n");
				} else if(strncmp(input, "c", 1) == 0) {
					printf("cmd: c\n");
				} else if(strncmp(input, "d", 1) == 0) {
					printf("cmd: d\n");
				} else {
					printf("not supported input\n");
				}
			}
			if(FD_ISSET(conndfd, &rfds)) {
				n = recv(conndfd,buf,sizeof(buf), 0);
				printf("recv: ");
				for(i = 0; i < n; i++) {
					printf("%02x ", buf[i]);
				}
				printf("\n");
			}
		}
	}

	close(conndfd);
	return 0;
}
