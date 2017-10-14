#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <bpclient_config.h>
#include <bp_public.h>
#include <bp_make_fix_head.h>
#include <bp_pack_type.h>
#include <bp_vrb_flags.h>
#include <bp_crc32.h>

#define PORT 8025
#define SERVER_IP "127.0.0.1"
int main()
{
	int conndfd;
	struct sockaddr_in serverAddr;
	int n;
	int len;
	int i;

	BP_UINT8 * user_name = "Ansersion";
	BP_UINT8 * password = "a123456";

	BP_UINT8 buf[2048+1];
	BP_UINT8 * pbuf = buf;
	BP_UINT16 client_id = 0;
	BP_UINT16 alive_time = 0x000f;
	BP_UINT8 timeout = 0xC;
	BP_WORD rmn_len = 0;
	BP_UINT32 crc = 0;

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


	pbuf = BP_make_fix_head(pbuf, BP_PACK_TYPE_CONNECT_MSK, 0);

	*pbuf++ = BP_LEVEL;
	rmn_len++;

	*pbuf++ = BP_VRB_FLAG_USER_NAME_MSK | BP_VRB_FLAG_PASSWORD_MSK | BP_VRB_FLAG_DEV_LOGIN_MSK;
	rmn_len++;

	pbuf = BP_SetBig16(pbuf, client_id);
	rmn_len += 2;

	pbuf = BP_SetBig16(pbuf, alive_time);
	rmn_len += 2;

	*pbuf++ = timeout;
	rmn_len++;

	pbuf = BP_Set2ByteField(pbuf, user_name, strlen(user_name));
	rmn_len += strlen(user_name) + 2;

	pbuf = BP_Set2ByteField(pbuf, password, strlen(password));
	rmn_len += strlen(password) + 2;

	*pbuf++ = BP_CLIENT_ID_LEN;
	rmn_len++;

	BP_SetNet16(pbuf, 0);
	rmn_len += 2;

	pbuf = buf;
	rmn_len += 4;
	BP_make_fix_head(pbuf, BP_PACK_TYPE_CONNECT_MSK, rmn_len);

	pbuf = buf;
	crc = BP_calc_crc32(pbuf, rmn_len-4+2);

	BP_SetBig32((buf+rmn_len+2-4), crc);

	for(i = 0; i < rmn_len + 2; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");

	n=send(conndfd,buf,rmn_len + 2,0);

	while(1) {
		sleep(1);
	}
	// n=recv(conndfd,buf,2048,0);

	// printf("Recv %d byte from Server\n",n);
	// printf("%s\n",buf);
	close(conndfd);
	return 0;
}
