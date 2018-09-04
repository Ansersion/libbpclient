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
#define SERVER_IP "127.0.0.1"

void printNote();
int handleUserInput();
int handleNetMsgReceived();
int bpDo();

int SetFlag = 0;
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

    printNote();

    /* connect to BcServer */
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
        FD_SET(stdinfd, &efds);
        FD_SET(conndfd, &efds);
        tv.tv_sec = 120;
        tv.tv_usec = 0;
        retval = select(conndfd+1, &rfds, NULL, &efds, &tv);
        if(-1 == retval) {
            /* error occurred, terminate the program */
            perror("select() error");
            err = -1;
            loop = 0;
        } else if(0 == retval) {
            // printf("timeout %d seconds", timeout);
        } else if(FD_ISSET(stdinfd, &rfds)) {
            if(0 != (err = handleUserInput())) {
                loop = 0;
            }
        } else if(FD_ISSET(conndfd, &rfds)) {
            if(0 != (err = handleNetMsgReceived())) {
                loop = 0;
            }
        }
        if(0 != (err = bpDo())) {
            loop = 0;
        }

    }

    close(conndfd);
    return err;
}

void printNote()
{
    printf("***********Virtual BcClient(%s)***********\r\n", VERSION);
    printf("It's a example of libbpclient\r\n");
    printf("More Info: https://github.com/Ansersion/libbpclient \r\n");
    printf("Input \"h\" for help\r\n");
}

int handleUserInput()
{
    const int MAX_PARA_NUM = 5;
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
    if(strcmp(cmd, "h") == 0) {
        /* paraNum - 1: last one is '\r\n' which is not a parameter */
        for(i = 0; i < paraNum - 1; i++) {
            printf("%s ", paras[i]);
        }
        printf("\r\n");
    } else if(strcmp(cmd, "set") == 0) {
    } else if(strcmp(cmd, "get") == 0) {
    } else if(strcmp(cmd, "bye") == 0) {
    } else {
        printf("Unknown command: %s\r\n", cmd);
    }
    return 0;
}

int handleNetMsgReceived()
{
    return 0;
}

int bpDo() {
    int err = 0;
    if(SetFlag) {
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
