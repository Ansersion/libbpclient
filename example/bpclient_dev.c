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
#include <bp_report.h>
#include <bp_getack.h>
#include <bp_postack.h>
#include <bp_ping.h>
#include <bp_sig_table.h>
#include <bp_sig_table_tools.h>


#define PORT 8025
#define SERVER_IP "127.0.0.1"

// BP_UINT8 DEV_NAME[] = "AnsersionDev";

int main()
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

	// BP_UINT8 * user_name = "2";
	// BP_UINT8 * password = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
	BP_UINT8 * TEST = "TST";
	BP_UINT8 * user_name = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1";
	BP_UINT8 * password = "1111111111111111111111111111111111111111111111111111111111111111";

	BP_UINT8 buf[2048+1];
	BP_UINT16 left_len;
	BP_UINT32 crc = 0;
	BP_UINT8 type_and_flags;
    const BPContext * bpContextTmp = BP_NULL;

	PackBuf pack_buf;
	PackBuf * p_pack_buf;
	BP_ConnackStr str_connack;
	BP_PingackStr str_pingack;
	BP_GetStr str_get;
	BP_PostStr str_post;
	BP_SigId2Val sig_id_2_val_array_test[1];
	sig_id_2_val_array_test[0].SigId = SIG_SYS_POWER;
	sig_id_2_val_array_test[0].SigVal.t_enm = 1;

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

	// BP_Init2Default(&BPContextEmbeded);
    BP_InitEmbededContext();

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
				if(strncmp(input, "o", 1) == 0) {
					printf("cmd: o\n");
				} else if(strncmp(input, "rsc", 3) == 0){
					// p_pack_buf = BP_PackReport(BP_NULL, g_SysSigMap);
					// p_pack_buf = BP_PackReport(DEV_NAME, g_SysSigMap, BP_NULL, g_SysSigMapSize);
					// n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					// if(n != p_pack_buf->MsgSize) {
					// 	close(conndfd);
					// 	perror("Send error");
					// 	return -1;
					// }
					// printf("report\n");
				} else if(strncmp(input, "rsm", 3) == 0){
					// p_pack_buf = BP_PackReport(BP_NULL, g_SysSigMap);
					p_pack_buf = BP_PackReportSigTable(&BPContextEmbeded, g_SysSigMap, g_SysSigMapSize);
					// n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					// if(n != p_pack_buf->MsgSize) {
					// 	close(conndfd);
					// 	perror("Send error");
					// 	return -1;
					// }
					printf("report\n");
				} else if(strncmp(input, "rsv", 3) == 0){
					// p_pack_buf = BP_PackReportSigVal(&sig_id_2_val_array_test, sizeof(sig_id_2_val_array_test) / sizeof(BP_SigId2Val), BP_NULL, 0);
					if(BP_NULL == p_pack_buf) {
						printf("p_pack_buf == NULL\n");
					} else if(BP_NULL == p_pack_buf->PackStart) {
						printf("p_pack_buf->PackStart == NULL\n");
					} else {
						printf("MsgSize: %d\n", p_pack_buf->MsgSize);
					}
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
                    printf("start pack connect\n");
					p_pack_buf = BP_PackConnect(&BPContextEmbeded, user_name, password);
                    printf("start send:%p\n", p_pack_buf);
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
						close(conndfd);
						perror("Send error");
						return -1;
					}
					printf("connect\n");
				} else if(strncmp(input, "d", 1) == 0) {
					p_pack_buf = BP_PackDisconn(&BPContextEmbeded);
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
						close(conndfd);
						perror("Send error");
						return -3;
					}
					printf("disconn\n");
					loop = 0;
				} else if(strncmp(input, "p", 1) == 0) {
					p_pack_buf = BP_PackPing(&BPContextEmbeded);
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
						close(conndfd);
						perror("Send error");
						return -3;
					}
					printf("ping\n");
				} else if(strncmp(input, "t", 1) == 0) {
					n=send(conndfd,TEST,strlen(TEST),0);
					printf("START TEST\n");
				} else {
					printf("not supported input\n");
				}
			}
			if(FD_ISSET(conndfd, &rfds)) {
				n=recv(conndfd,buf,FIX_HEAD_SIZE, MSG_WAITALL);
				if(strncmp(buf, TEST, 3) == 0) {
					printf("recv %s\n", TEST);
					continue;
				}
				if(FIX_HEAD_SIZE != n) {
					close(conndfd);
					perror("Recv error 1");
					return -2;
				}
				BP_ParseFixHead(buf, &type_and_flags, &left_len);

				len = left_len;
                printf("len=%d\n", len);

				n += recv(conndfd,buf+FIX_HEAD_SIZE,len, MSG_WAITALL);
				len += FIX_HEAD_SIZE;

				if(n != len) {
					close(conndfd);
					printf("Recv error 2");
					return -2;
				}
                printf("recv: \n");
                for(i = 0; i < len; i++) {
                    printf("%02x ", buf[i]);
                }
                printf("\n");

				if(0 != BP_CheckCRC(type_and_flags, buf, len)) {
					printf("CRC Check error\n");
					continue;
				}
				switch((type_and_flags >> 4) & 0x0F) {
					case BP_PACK_TYPE_CONNACK:
						BP_ParseConnack(&str_connack, buf, len);
						printf("CONNACK:\n");
						printf("RetCode = %d\n", str_connack.RetCode);
						printf("client id = %d\n", str_connack.ClientID);
						printf("system signal set version = %d\n", str_connack.SysSigSetVersion);
						break;
					case BP_PACK_TYPE_RPRTACK:
						printf("RPRTACK:\n");
						for(i = 0; i < len; i++) {
							printf("%02x ", buf[i]);
						}
						printf("\n");
						break;
					case BP_PACK_TYPE_PINGACK:
						printf("PINGACK:\n");
						for(i = 0; i < len; i++) {
							printf("%02x ", buf[i]);
						}
						printf("\n");
						BP_ParsePingack(&str_pingack, buf, len);
						printf("flags = %d\n", str_pingack.Flags);
						// printf("client id = %d\n", str_pingack.ClientID);
						printf("seq id = %d\n", str_pingack.SeqId);
						printf("ret code = %d\n", str_pingack.RetCode);
						break;
					case BP_PACK_TYPE_POST:
						printf("POST:%d\n", len);
						for(i = 0; i < len; i++) {
							printf("%02x ", buf[i]);
						}
						printf("\n");
						BP_ParsePost(&str_post, buf, len);
						printf("Flags: %x\t", str_post.Flags);
						printf("ClientID: %x\t", str_post.ClientID);
						printf("SeqId: %x\t", str_post.SeqId);
						for(i = 0; i < str_post.SigNum; i++) {

							printf("%x->%x ", str_post.SigArray[i].SigId, str_post.SigArray[i].SigVal.t_enm);
						}
						printf("\n");

						if(0 != BP_SetSigVal(str_post.SigNum, str_post.SigArray)) {
							printf("SetSigVal error\n");
						} 
						printf("start dump...\n");
						BP_SigDump();

						// p_pack_buf = BP_PackPostack(&str_post);
						printf("MsgSize: %d\n", p_pack_buf->MsgSize);
						for(i = 0; i < p_pack_buf->MsgSize; i++) {
							printf("%02x ", p_pack_buf->PackStart[i]);
						}
						printf("\n");
						n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
						if(n != p_pack_buf->MsgSize) {
							close(conndfd);
							perror("Send error");
							return -1;
						}
						printf("post\n");
						break;
					case BP_PACK_TYPE_GET:
						printf("GETACK:%d\n", len);
						for(i = 0; i < len; i++) {
							printf("%02x ", buf[i]);
						}
						printf("\n");
						BP_ParseGet(&str_get, buf, len);
						printf("Flags: %x\t", str_get.Flags);
						printf("ClientID: %x\t", str_get.ClientID);
						printf("SeqId: %x\t", str_get.SeqId);
						printf("SigNum: %x\n", str_get.SigNum);
						for(i = 0; i < str_get.SigNum; i++) {
							printf("%x ", str_get.SigTabArray[i].SigId);
						}
						printf("\n");

						// p_pack_buf = BP_PackGetack(&str_get);
						printf("MsgSize: %d\n", p_pack_buf->MsgSize);
						for(i = 0; i < p_pack_buf->MsgSize; i++) {
							printf("%02x ", p_pack_buf->PackStart[i]);
						}
						printf("\n");
						n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
						if(n != p_pack_buf->MsgSize) {
							close(conndfd);
							perror("Send error");
							return -1;
						}
						printf("getack\n");
						break;
					default:
						printf("recv pack unknown\n");
						for(i = 0; i < len; i++) {
							printf("%02x ", buf[i]);
						}
						printf("\n");
				}
			}
		}
	}

	close(conndfd);
	return 0;
}
