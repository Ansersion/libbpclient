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


#define VERSION "v0.1"
#define PORT 8025
#define SINGLE_DEVICE_SERVER_PORT 8024
#define REPORT_FLAG_SIG_MAP 1
#define REPORT_FLAG_SIG_MAP_CHECKSUM 2
#define REPORT_FLAG_CUS_SIG_VALUE 3
#define REPORT_FLAG_SYS_SIG_VALUE 4

void printNote();
int handleUserInput();
int handleNetMsgReceived(int fd);
int bpDo();

int conndfd;
int singleDeviceFd;
int client_sock_fd;
BP_UINT8 recvBuf[2048+1];
char input[256];

int SetFlag = 0;
int ConnectFlag = 0;
int ReportFlag = 0;
int SignalType = 0xFF;
BP_UINT16 SetSignalId;
void * SetSignalValue;
void * Sn;
void * Password;
BP_PostackStr str_postack;
BP_SpecackStr str_specack;;
int PostFlag = 0;
int ByeFlag = 0;
int PingFlag = 0;
int PingAutoTime = 0;
int SpecsetFlag = 0;

int main()
{
    const int stdinfd = 0;
    const int timeout = 1;
    int loop;
	struct sockaddr_in serverAddr;
	struct sockaddr_in singleServerAddr;
    int err = 0;
    int retval;
	fd_set rfds;
	fd_set efds;
	struct timeval tv;
	char serverIp[64];
    int timeoutCount = 0;

	SetSignalValue = malloc(256);
	Sn = malloc(256);
	Password = malloc(256);

    printNote();
	printf("* Please Input BcServer Ip: ");
	scanf("%s", serverIp);

    printf("* Input \"help\" for help\r\n");
    fgets(input, sizeof(input), stdin);

    /* connect to BcServer */
	if(-1==(conndfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))) {
		printf("* Create Socket Error\n");
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(serverIp);
	serverAddr.sin_port=htons(PORT);
	if(connect(conndfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0) {
		printf("* Connect Error\n");
		return -1;
	}

    /* initialize the signal device server */
	memset(&singleServerAddr,0,sizeof(singleServerAddr));
    singleServerAddr.sin_family= AF_INET;    //IPV4
    singleServerAddr.sin_port = htons(SINGLE_DEVICE_SERVER_PORT);
    singleServerAddr.sin_addr.s_addr = INADDR_ANY;  //指定的是所有地址
        //creat socket
    if( (singleDeviceFd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) {
        perror("creat failure");
        return -1;
    }

    //bind soucket
    if(bind(singleDeviceFd, (const struct sockaddr *)&singleServerAddr,sizeof(singleServerAddr)) < 0) {
        perror("bind failure");
        return -1;
    }

    //listen
    if(listen(singleDeviceFd, 1) < 0) {
        perror("listen failure");
        return -1;
    }


    /* initialize BP embeded context */
    /* you could also define your own BPContext */
    BP_InitEmbededContext();

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    loop = 1;
    while(loop) {
        FD_ZERO(&rfds);
        FD_SET(stdinfd, &rfds);
        FD_SET(conndfd, &rfds);
        FD_SET(singleDeviceFd, &rfds);
        retval = select(singleDeviceFd+1, &rfds, NULL, NULL, &tv);
        if(-1 == retval) {
            /* error occurred, terminate the program */
            perror("* select() error");
            err = -1;
            loop = 0;
        } else if(0 == retval) {
            // printf("* timeout\n");
			tv.tv_sec = timeout;
			tv.tv_usec = 0;
            timeoutCount++;
        } else if(FD_ISSET(stdinfd, &rfds)) {
			FD_CLR(stdinfd, &rfds);
            if(0 != (err = handleUserInput())) {
                loop = 0;
            }
            timeoutCount = 0;
        } else if(FD_ISSET(conndfd, &rfds)) {
			FD_CLR(conndfd, &rfds);
            if(0 != (err = handleNetMsgReceived(conndfd))) {
                loop = 0;
            }
            timeoutCount = 0;
        } else if(FD_ISSET(singleDeviceFd, &rfds)) {
            struct sockaddr_in client_address;
            socklen_t address_len;
            FD_CLR(singleDeviceFd, &rfds);
            client_sock_fd = accept(singleDeviceFd,(struct sockaddr *)&client_address, &address_len);
            if(client_sock_fd > 0) {
                int n;
                int i = 0;
                PackBuf * p_pack_buf;
                err = handleNetMsgReceived(client_sock_fd);
                if(err == -100) {
                }
                printf("* accepted\r\n");
                char full_message[]="the client is full!can't join!\n";
                // bzero(input_message,BUFF_SIZE);
                // strncpy(input_message, full_message,100);
                // send(client_sock_fd, full_message, strlen(full_message), 0);
                // close(client_sock_fd);
                p_pack_buf = BP_PackSpecack(&BPContextEmbeded, &str_specack);
                printf("main debug: %d\n", p_pack_buf->MsgSize);
                for(i = 0; i < p_pack_buf->MsgSize; i++) {
                    printf("%02x ", p_pack_buf->PackStart[i]);
                }
                printf("\n");
                n=send(client_sock_fd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
                if(n != p_pack_buf->MsgSize) {
                    perror("* Send error");
                }
                printf("* specack\n");
                close(client_sock_fd);

            }
            timeoutCount = 0;

        }
        if(PingAutoTime > 0) {
            if(timeoutCount > PingAutoTime) {
                timeoutCount = 0;
                PingFlag = 1;
            }
        }
        if(0 != (err = bpDo())) {
            loop = 0;
        }

    }

    close(conndfd);
    close(singleDeviceFd);
	free(SetSignalValue);
	free(Sn);
	free(Password);
    return err;
}

void printNote()
{
    printf("***********Virtual BcClient(%s)***********\r\n", VERSION);
    printf("* It's a example of libbpclient\r\n");
    printf("* More Info: https://github.com/Ansersion/libbpclient \r\n");
}

int handleUserInput()
{
	/* last one is '\r\n' which is not a parameter */
    const int MAX_PARA_NUM = 5 + 1;
    char * tmp;
    char * tmp2;
    char * cmd;
    char * paras[MAX_PARA_NUM];
    int paraNum = 0;
    int i;
    int tmpInt;
        
    if(NULL == fgets(input, sizeof(input), stdin)) {
        perror("fgets() error");
        return -2;
    }
    tmp = strtok(input, " ");
    cmd = tmp;
    while(tmp && paraNum < MAX_PARA_NUM) {
        tmp = strtok(NULL, " ");
        paras[paraNum++] = tmp;
    }
    if(NULL == cmd) {
        return 0;
    }
    if(paraNum >= 2) {
        tmp2 = strstr(paras[paraNum - 2], "\r");
        if(tmp2) {
            *tmp2 = '\0';
        }
        tmp2 = strstr(paras[paraNum - 2], "\n");
        if(tmp2) {
            *tmp2 = '\0';
        }
    } else {
        tmp2 = strstr(cmd, "\r");
        if(tmp2) {
            *tmp2 = '\0';
        }
        tmp2 = strstr(cmd, "\n");
        if(tmp2) {
            *tmp2 = '\0';
        }
    }
    if(strncmp(cmd, "help", strlen("help")) == 0) {
		printf("* help --- print this message\r\n");
		printf("* connect <SN> <Password> --- connect to the BcServer with device SN and password, such as 'connect abc abc_password'\r\n");
		printf("* get <SignalId> <SignalType> --- get the signal value, such as 'get 4 E002'\r\n");
		printf("* set <SignalId> <SignalType> <SignalValue> --- set the signal value, such as 'set E002 4 0'\r\n");
		printf("* report map/checksum/sysvals/cusvals --- report signal map or signal map checksum or all system signal values or all custom signal values, such as 'report map'\r\n");
		printf("* ping <option> <para> --- tell the server I'm still alive,(<option>:'auto',<para> int(in unit of second)), such as 'ping', 'ping auto 10'\r\n");
		printf("* bye --- quit\r\n");
		printf("* Note: <SignalType>: 0-u32, 1-u16, 2-i32, 3-i16, 4-enum, 5-float, 6-string, 7-boolean\r\n");
    } else if(strncmp(cmd, "connect", strlen("connect")) == 0) {
		if(paraNum < 3) {
			printf("* too few parameter\r\n");
			return 0;
		} 
		if(sscanf(paras[0], "%x", &SetSignalId) < 0) {
			printf("* invalid signal id[%s]\r\n", paras[0]);
			return 0;
		}
		memcpy(Sn, paras[0], strlen(paras[0]) + 1);
		memcpy(Password, paras[1], strlen(paras[1]) + 1);
		ConnectFlag = 1;
    } else if(strncmp(cmd, "set", strlen("set")) == 0) {
		if(paraNum < 4) {
			printf("* too few parameter\r\n");
			return 0;
		} 
		if(sscanf(paras[0], "%x", &SetSignalId) < 0) {
			printf("* invalid signal id[%s]\r\n", paras[0]);
			return 0;
		}
		if(sscanf(paras[1], "%d", &SignalType) < 0) {
			printf("* invalid signal type[%s]\r\n", paras[1]);
			return 0;
		}
		memcpy(SetSignalValue, paras[2], strlen(paras[2]));
		SetFlag = 1;
    } else if(strncmp(cmd, "get", strlen("get")) == 0) {
        BP_SigId2Val * sig_id_2_val_tmp = BP_NULL;
		if(paraNum < 3) {
			printf("* too few parameter\r\n");
			return 0;
		} 
		if(sscanf(paras[0], "%x", &SetSignalId) < 0) {
			printf("* invalid signal id[%s]\r\n", paras[0]);
			return 0;
		}
		if(sscanf(paras[1], "%d", &SignalType) < 0) {
			printf("* invalid signal id[%s]\r\n", paras[1]);
			return 0;
		}
        if(0 <= SetSignalId && SetSignalId < SYSTEM_SIGNAL_ID_START) {
            // TODO
        } else if(SetSignalId >= SYSTEM_SIGNAL_ID_START) {
            for(i = 0; i < g_SysSigNum; i++) {
                if(g_SysSigId2Val[i].SigId == SetSignalId) {
                    sig_id_2_val_tmp = &g_SysSigId2Val[i];
                    break;
                }
            }
        }
        if(BP_NULL == sig_id_2_val_tmp) {
            printf("* Not find the signal\r\n");
        } else {
            switch(SignalType) {
                case SIG_TYPE_U32:
                    printf("* %x->%d\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_u32);
                    break;
                case SIG_TYPE_U16:
                    printf("* %x->%d\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_u16);
                    break;
                case SIG_TYPE_I32:
                    printf("* %x->%d\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_i32);
                    break;
                case SIG_TYPE_I16:
                    printf("* %x->%d\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_i16);
                    break;
                case SIG_TYPE_ENM:
                    printf("* %x->%d\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_enm);
                    break;
                case SIG_TYPE_FLT:
                    printf("* %x->%f\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_flt);
                    break;
                case SIG_TYPE_STR:
                    printf("* %x->%s\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_str);
                    break;
                case SIG_TYPE_BOOLEAN:
                    printf("* %x->%d\r\n", SetSignalId, sig_id_2_val_tmp->SigVal.t_bool);
                    break;
            }
        }
    } else if(strncmp(cmd, "report", strlen("report")) == 0) {
		if(paraNum < 2) {
			printf("* too few parameter\r\n");
			return 0;
		} 
		if(0 == strncmp(paras[0], "map", strlen("map"))) {
            ReportFlag = REPORT_FLAG_SIG_MAP;
		}
		if(0 == strncmp(paras[0], "cusvals", strlen("map"))) {
            ReportFlag = REPORT_FLAG_CUS_SIG_VALUE;
		}
		if(0 == strncmp(paras[0], "sysvals", strlen("map"))) {
            ReportFlag = REPORT_FLAG_SYS_SIG_VALUE;
		}
		if(0 == strncmp(paras[0], "checksum", strlen("checksum"))) {
            ReportFlag = REPORT_FLAG_SIG_MAP_CHECKSUM;
		}
    } else if(strncmp(cmd, "ping", strlen("ping")) == 0) {
        if(paraNum >= 2) {
            tmpInt = atoi(paras[1]);
            if(0 == strncmp(paras[0], "auto", strlen("auto"))) {
                PingAutoTime = tmpInt;
            }
        } else {
            PingFlag = 1;
        }
    } else if(strncmp(cmd, "bye", strlen("bye")) == 0) {
		ByeFlag = 1;
    } else {
        printf("* Unknown command: [%s]\r\n", cmd);
    }
    return 0;
}

int handleNetMsgReceived(int fd)
{
    int n;
	BP_UINT16 left_len;
	BP_UINT32 crc = 0;
	BP_UINT8 type_and_flags;
    int i;
    int len;
	BPPacket bp_packet;

    n=recv(fd,recvBuf,FIX_HEAD_SIZE, MSG_WAITALL);
    if(FIX_HEAD_SIZE != n) {
        perror("Recv error 1\r\n");
        return -2;
    }
    if(0 != BP_ParseFixHead(recvBuf, &type_and_flags, &left_len)) {
        perror("Recv error 1\r\n");
        return -4;
    }

    if((type_and_flags & 0x01) != CHECKSUM_TYPE) {
        printf("* crc unmatched\r\n");
        return -100;
    }

    len = left_len;
    printf("* len=%d\r\n", len);

    n += recv(fd,recvBuf+FIX_HEAD_SIZE,len, MSG_WAITALL);
    len += FIX_HEAD_SIZE;

    if(n != len) {
        printf("* Recv error 2\r\n");
        return -2;
    }
    printf("* recv: ");
    for(i = 0; i < len; i++) {
        printf("%02x ", recvBuf[i]);
    }
    printf("\n");

    if(0 != BP_CheckCRC(type_and_flags, recvBuf, len)) {
        printf("* CRC Check error\n");
        return -3;
    }
    printf("flags: %02x\n", type_and_flags);
    switch((type_and_flags >> 4) & 0x0F) {
        case BP_PACK_TYPE_CONNACK: {
                BP_ConnackStr str_connack;
                if(0 == BP_ParseConnack(&BPContextEmbeded, &str_connack, recvBuf, len)) {
                    printf("* CONNACK OK:\n");
                }
                printf("* RetCode = %d\n", str_connack.RetCode);
                printf("* system signal set version = %d\n", str_connack.Level);
                printf("* current server index = %d\n", BPContextEmbeded.CurrentServerNodeIndex);
                for(i = 0; i < BPContextEmbeded.ServerChainSize; i++) {
                    printf("* %d: ", i);
                    ServerNodeDump(&BPContextEmbeded.ServerChain[i]);
                }
                break;
            }
        case BP_PACK_TYPE_RPRTACK: {
                BP_RprtackStr str_rprtack;
                if(BP_ParseRprtack(&BPContextEmbeded, &str_rprtack, recvBuf, len) == 0) {
                    printf("* RPRTACK OK:\n");
                }
                printf("* RetCode = %d\n", str_rprtack.RetCode);
                printf("* SeqId = %d\n", str_rprtack.SeqId);
                break;
            }
		case BP_PACK_TYPE_PINGACK: {
				BP_PingackStr str_pingack;
                if(0 == BP_ParsePingack(&BPContextEmbeded, &str_pingack, recvBuf, len)) {
                    printf("* PINGACK:\n");
                    printf("* flags = %d\n", str_pingack.Flags);
                    printf("* seq id = %d\n", str_pingack.SeqId);
                    printf("* ret code = %d\n", str_pingack.RetCode);
                }
				break;
			}
		case BP_PACK_TYPE_POST: {
                int x;
                BP_PostStr str_post;
				printf("* POST:%d\n", len);
                x = BP_ParsePost(&str_post, recvBuf, len);
                str_postack.Flags = str_post.Flags;
                str_postack.SeqId = str_post.SeqId;
                printf("* ParsePost Flags: %x\n", str_post.Flags);
                printf("* ParsePost seqId: %x\n", str_post.SeqId);
				if(0 != x) {
                    printf("* ParsePost err: %x\n", x);
                    /* 0x06 -> device error */
                    str_postack.RetCode = 0x06;
                } else {
                    /* 0 -> OK */
                    str_postack.RetCode = 0;
                }
                PostFlag = 1;
				break;
			}
		case BP_PACK_TYPE_SPECSET: {
                int x;
                BP_SpecsetStr str_specset;
                BP_UINT8 ssid[64];
                BP_UINT8 ssidPass[64];
                BP_UINT8 userName[64];
                str_specset.Ssid = ssid;
                str_specset.Password = ssidPass;
                str_specset.UserName = userName;

                x = BP_ParseSpecset(&BPContextEmbeded, &str_specset, recvBuf, len);
				if(0 != x) {
                    printf("* ParseSpecset err: %x\n", x);
                    /* 0x06 -> device error */
                    str_specack.Type = str_specset.Type;
                    str_specack.RetCode = 0x06;
                } else {
                    /* 0 -> OK */
                    str_specack.Type = str_specset.Type;
                    str_specack.RetCode = 0;
                    ssid[str_specset.SsidLen] = '\0';
                    ssidPass[str_specset.PasswordLen] = '\0';
                    userName[str_specset.UserNameLen] = '\0';
                    printf("* :%s,%s,%s: \n", ssid, ssidPass, userName);
                }
                SpecsetFlag = 1;
				break;
			}
        default: {
				printf("* recv pack unknown\n");
				break;
			}
    }
    return 0;
}

int bpDo() {
    int err = 0;
    int n;
    int i;
	PackBuf * p_pack_buf;
    if(ConnectFlag) {
        printf("* start connect\n");
        p_pack_buf = BP_PackConnect(&BPContextEmbeded, Sn, Password);
        printf("* start send:%p\n", p_pack_buf);
        n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
        if(n != p_pack_buf->MsgSize) {
            perror("* Send error");
            err = -1;
        }
        ConnectFlag = 0;
    }
    if(SetFlag) {
        BP_SigId2Val * sig_id_2_val_tmp = BP_NULL;
        if(0 <= SetSignalId && SetSignalId < SYSTEM_SIGNAL_ID_START) {
            // TODO
        } else if(SetSignalId >= SYSTEM_SIGNAL_ID_START) {
            for(i = 0; i < g_SysSigNum; i++) {
                if(g_SysSigId2Val[i].SigId == SetSignalId) {
                    sig_id_2_val_tmp = &g_SysSigId2Val[i];
                    break;
                }
            }
        }

        if(BP_NULL != sig_id_2_val_tmp) {

            sig_id_2_val_tmp->SigId = SetSignalId;
            switch(SignalType) {
                case SIG_TYPE_U32:
                    sscanf(SetSignalValue, "%u", &(sig_id_2_val_tmp->SigVal.t_u32));
                    break;
                case SIG_TYPE_U16:
                    sscanf(SetSignalValue, "%u", &(sig_id_2_val_tmp->SigVal.t_u16));
                    break;
                case SIG_TYPE_I32:
                    sscanf(SetSignalValue, "%d", &(sig_id_2_val_tmp->SigVal.t_i32));
                    break;
                case SIG_TYPE_I16:
                    sscanf(SetSignalValue, "%d", &(sig_id_2_val_tmp->SigVal.t_i16));
                    break;
                case SIG_TYPE_ENM:
                    sscanf(SetSignalValue, "%u", &(sig_id_2_val_tmp->SigVal.t_enm));
                    break;
                case SIG_TYPE_FLT:
                    sscanf(SetSignalValue, "%f", &(sig_id_2_val_tmp->SigVal.t_flt));
                    break;
                case SIG_TYPE_STR:
                    sig_id_2_val_tmp->SigVal.t_str = SetSignalValue;
                    break;
                case SIG_TYPE_BOOLEAN:
                    sscanf(SetSignalValue, "%d", &(sig_id_2_val_tmp->SigVal.t_bool));
                    break;
                default:
                    err = -1;
                    printf("* Unknown signal type: %d\n", SignalType);
                    break;
            }
            if(0 == err) {
                // p_pack_buf = BP_PackReportSigVal(&BPContextEmbeded, sig_id_2_val_tmp, 1);
                p_pack_buf = BP_PackReport1SigVal(&BPContextEmbeded, sig_id_2_val_tmp);
                printf("* report signal value\n");
                n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
                if(n != p_pack_buf->MsgSize) {
                    perror("* Send error");
                    err = -1;
                }
            }
        }


        SetFlag = 0;
    }
	if(PingFlag) {
		p_pack_buf = BP_PackPing(&BPContextEmbeded);
		n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
		if(n != p_pack_buf->MsgSize) {
			perror("Send error");
			err = -1;
		}
		printf("* ping\n");
		PingFlag = 0;
	}
    if(ByeFlag) {
        p_pack_buf = BP_PackDisconn(&BPContextEmbeded);
        n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
        if(n != p_pack_buf->MsgSize) {
            perror("* Send error");
        }
        printf("* disconn\n");
        ByeFlag = 0;
    }
    if(PostFlag) {
        p_pack_buf = BP_PackPostack(&BPContextEmbeded, &str_postack);
        n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
        if(n != p_pack_buf->MsgSize) {
            perror("* Send error");
        }
        printf("* postack\n");
        PostFlag = 0;
    }
    if(ReportFlag) {
        switch(ReportFlag) {
            case REPORT_FLAG_SIG_MAP:
					printf("* report signal map\n");
					p_pack_buf = BP_PackReportSigTable(&BPContextEmbeded);
					n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
					if(n != p_pack_buf->MsgSize) {
                        perror("* Send error");
                        err = -1;
					}
                break;
            case REPORT_FLAG_SIG_MAP_CHECKSUM:
                printf("* report checksum\n");
                p_pack_buf = BP_PackReportSigTabChksum(&BPContextEmbeded);
                n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
                if(n != p_pack_buf->MsgSize) {
                    perror("* Send error");
                    err = -1;
                }
                break;
            case REPORT_FLAG_CUS_SIG_VALUE:
                printf("* report custom signal values\n");
                p_pack_buf = BP_PackReportAllCusSigVal(&BPContextEmbeded);
                n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
                if(n != p_pack_buf->MsgSize) {
                    perror("* Send error");
                    err = -1;
                }
                break;
            case REPORT_FLAG_SYS_SIG_VALUE:
                printf("* report system signal values\n");
                p_pack_buf = BP_PackReportAllSysSigVal(&BPContextEmbeded);
                n=send(conndfd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
                if(n != p_pack_buf->MsgSize) {
                    perror("* Send error");
                    err = -1;
                }
                break;
        }
        ReportFlag = 0;
    }
    /*
    if(SpecsetFlag) {
        p_pack_buf = BP_PackSpecack(&BPContextEmbeded, &str_specack);
        printf("* specack %d\n", client_sock_fd);
        n=send(client_sock_fd,p_pack_buf->PackStart,p_pack_buf->MsgSize,0);
        if(n != p_pack_buf->MsgSize) {
            perror("* Send error");
        }
        printf("* specack\n");
        close(client_sock_fd);
        SpecsetFlag = 0;
    }
    */
    return err;
}
