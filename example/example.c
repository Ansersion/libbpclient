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
#define SERVER_IP "192.168.2.196"

void printNote();
int handleUserInput();
int handleNetMsgReceived();
int bpDo();

int SetFlag = 0;
int ConnectFlag = 0;
int SignalType = 0xFF;
BP_UINT16 SetSignalId;
void * SetSignalValue;
void * Sn;
void * Password;
int PostFlag = 0;
int ByeFlag = 0;

int main()
{
    const int stdinfd = 0;
    const int timeout = 30;
    int loop;
	int conndfd;
	struct sockaddr_in serverAddr;
    int err = 0;
    int retval;
	fd_set rfds;
	fd_set efds;
	struct timeval tv;
	char serverIp[64];

	SetSignalValue = malloc(256);
	Sn = malloc(256);
	Password = malloc(256);

    printNote();
	printf("Please Input BcServer Ip: ");
	scanf("%s", serverIp);

    printf("Input \"help\" for help\r\n");

    /* connect to BcServer */
	if(-1==(conndfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))) {
		printf("Create Socket Error\n");
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(serverIp);
	serverAddr.sin_port=htons(PORT);
	if(connect(conndfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0) {
		printf("Connect Error\n");
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
        // FD_SET(stdinfd, &efds);
        // FD_SET(conndfd, &efds);
        retval = select(conndfd+1, &rfds, NULL, NULL, &tv);
        if(-1 == retval) {
            /* error occurred, terminate the program */
            perror("select() error");
            err = -1;
            loop = 0;
        } else if(0 == retval) {
            // printf("timeout %d seconds", timeout);
        } else if(FD_ISSET(stdinfd, &rfds)) {
			FD_CLR(stdinfd, &rfds);
            if(0 != (err = handleUserInput())) {
                loop = 0;
            }
        } else if(FD_ISSET(conndfd, &rfds)) {
			FD_CLR(conndfd, &rfds);
            if(0 != (err = handleNetMsgReceived())) {
                loop = 0;
            }
        }
        if(0 != (err = bpDo())) {
            loop = 0;
        }

    }

    close(conndfd);
	free(SetSignalValue);
	free(Sn);
	free(Password);
    return err;
}

void printNote()
{
    printf("***********Virtual BcClient(%s)***********\r\n", VERSION);
    printf("It's a example of libbpclient\r\n");
    printf("More Info: https://github.com/Ansersion/libbpclient \r\n");
}

int handleUserInput()
{
	/* last one is '\r\n' which is not a parameter */
    const int MAX_PARA_NUM = 5 + 1;
    char * tmp;
    char * cmd;
    char * paras[MAX_PARA_NUM];
    char input[256];
    int paraNum = 0;
    int i;
        
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
    if(strncmp(cmd, "help", strlen("help")) == 0) {
		printf("* help --- print this message\r\n");
		printf("* connect <SN> <Password> --- connect to the BcServer with device SN and password, such as 'connect abc abc_password'\r\n");
		printf("* set <SignalId> <SignalType> <SignalValue> --- set the signal value, such as 'set 4 E002 0'\r\n");
		printf("* get <SignalId> <SignalType> --- get the signal value, such as 'get 4 E002'\r\n");
		printf("* bye --- quit\r\n");
		printf("Note: <SignalType>: 0-u32, 1-u16, 2-i32, 3-i16, 4-enum, 5-float, 6-string, 7-boolean\r\n");
    } else if(strncmp(cmd, "connect", strlen("connect")) == 0) {
		if(paraNum < 3) {
			printf("too few parameter\r\n");
			return 0;
		} 
		if(sscanf(paras[0], "%x", &SetSignalId) < 0) {
			printf("invalid signal id[%s]\r\n", paras[0]);
			return 0;
		}
		memcpy(Sn, paras[0], strlen(paras[0]) + 1);
		memcpy(Password, paras[1], strlen(paras[1]) + 1);
		ConnectFlag = 1;
    } else if(strncmp(cmd, "set", strlen("set")) == 0) {
		if(paraNum < 4) {
			printf("too few parameter\r\n");
			return 0;
		} 
		if(sscanf(paras[0], "%x", &SetSignalId) < 0) {
			printf("invalid signal id[%s]\r\n", paras[0]);
			return 0;
		}
		if(sscanf(paras[1], "%d", &SignalType) < 0) {
			printf("invalid signal id[%s]\r\n", paras[1]);
			return 0;
		}
		memcpy(SetSignalValue, paras[2], strlen(paras[2]));
		SetFlag = 1;
    } else if(strncmp(cmd, "get", strlen("get")) == 0) {
		if(paraNum < 3) {
			printf("too few parameter\r\n");
			return 0;
		} 
		if(sscanf(paras[0], "%x", &SetSignalId) < 0) {
			printf("invalid signal id[%s]\r\n", paras[0]);
			return 0;
		}
		if(sscanf(paras[1], "%d", &SignalType) < 0) {
			printf("invalid signal id[%s]\r\n", paras[1]);
			return 0;
		}
		/* TODO: */
    } else if(strncmp(cmd, "bye", strlen("bye")) == 0) {
		ByeFlag = 1;
    } else {
        printf("Unknown command: [%s]\r\n", cmd);
    }
    return 0;
}

int handleNetMsgReceived()
{
    return 0;
}

int bpDo() {
    int err = 0;
    if(ConnectFlag) {
        ConnectFlag = 0;
    }
    if(SetFlag) {
		printf("%x->%s\r\n", SetSignalId, (char *)SetSignalValue);

        SetFlag = 0;
    }
    if(ByeFlag) {
        err = 0xFF;
        ByeFlag = 0;
    }
    if(PostFlag) {
        PostFlag = 0;
    }
    return err;
}
