#include "jogging.h"
#include <sys/wait.h>
#include <errno.h>


int servSock; //server socket descriptor
struct sockaddr_in servSockAddr; //server internet socket address
unsigned int servPort = 60000;
unsigned char op;       // client request
int clitSock; // client socket descriptor
struct sockaddr_in clitSockAddr; // client internet socket address
unsigned int clitLen;            // client internet socket address length
char recvBuffer[BUFSIZE];        // receive temporary buffer
char sendBuffer[BUFSIZE];        // receive temporary buffer
int recvMsgSize, sendMsgSize;    // recieve and send buffer size


void conn_process() {
    printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

    // ルート保存用変数
    int user_id = 0, route_id = 0;
    // ルート取り出し用変数
    SAVED_ROUTE_TABLE resp_data;
    FILE *fp;
    // レシーブバッファ初期化
    memset(&recvBuffer, 0, sizeof(recvBuffer));
    memset(&sendBuffer, 0, sizeof(sendBuffer));
    // op初期化
    op = 0x00;

    printf("start!\n");

    // データ受け取り
    while ((recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0)) > 0) {
        printf("recvMsgSize = %d\nreceive : [%s]\n", recvMsgSize, recvBuffer);
        op = recvBuffer[0];
        printf("0x%x\n", op);

        // ヘッダ確認・処理分岐
        if ( op == 0xa0 ) {
            // CALORIE_TABLE select
            CALORIE_TABLE resp_data = calorie_select();
            ct_tab2str_select(&sendBuffer[0], resp_data);
        } else if ( op == 0xb0 ) {
            // SAVED_ROUTE_TABLE select
            sscanf(recvBuffer, "%c\n%d\n%d", &op, &user_id, &route_id);
            fp = saved_route_select(user_id, route_id);
        } else if ( op == 0xb1 ) {
            // SAVED_ROUTE_TABLE update
            int errno;
            sscanf(recvBuffer, "%c\n%d\n%d", &op, &user_id, &route_id);
        } else if ( op == 0xc0 ) {
            // USEDLOG_TABLE select
            int n;
            USEDLOG_TABLE *resp_data;

            sscanf(recvBuffer, "%c\n%d", &op, &user_id);
            resp_data = usedlog_select(user_id, &n);
            ult_tab2str_select(sendBuffer, resp_data, n);
        } else if ( op == 0xc2 ) {
            // USEDLOG_TABLE insert
            int errno;
            USEDLOG_TABLE recv_data;

            recv_data = ult_str2tab_insert(recvBuffer);
            errno = usedlog_insert(recv_data);
            sprintf(sendBuffer, "%d\n", errno);
        } else if ( op == 0xd0 ) {
            // USER_TABLE select
            USER_TABLE resp_data;

            sscanf(recvBuffer, "%c\n%d", &op, &user_id);
            printf("user_id = %d\n", user_id);
            resp_data = user_select(user_id);
            ut_tab2str_select(sendBuffer, resp_data);
        } else if ( op == 0xd1 ) {
            // USER_TABLE update
            int errno;
            USER_TABLE recv_data;

            recv_data = ut_str2tab_update(recvBuffer);
            errno = user_update(recv_data);
            if (errno == 0) {
                sprintf(sendBuffer, "true\n");
            } else {
                printf("errno = %d\n", errno);
                sprintf(sendBuffer, "false\n");
            }
        } else if ( op == 0xd2 ) {
            // USER_TABLE insert
            USER_TABLE recv_data;

            recv_data = ut_str2tab_insert(recvBuffer);
            user_id = user_insert(recv_data);
            sprintf(sendBuffer, "%08d\n", user_id);
        }

        // 返信データ送信
        if ( op != 0xb0 || op != 0xb1 || op != 0xc0 ) {
            errno = 0;
            printf("send... [%s]\n", sendBuffer);
            while((sendMsgSize = send(clitSock, sendBuffer, BUFSIZE, 0)) > 0){
            }
            if ( sendMsgSize == -1 ) {
                printf("Error number : %d\n", errno);
            } else {
                printf("success!\n");
            }
        }
        // ファイル送信モード
        if ( op == 0xb0 || op == 0xc0 ) {
            while(fread(sendBuffer, BUFSIZE, 1, fp) > 0 ) {
                if((sendMsgSize = send(clitSock, sendBuffer, BUFSIZE, 0)) < 0){
                    perror("send() failed.");
                    pthread_exit(&sendMsgSize);
                } else if(sendMsgSize == 0){
                    fprintf(stderr, "connection closed by foreign host.\n");
                    break;
                }
            }
        }


        // ファイル受信モード
        if ( op == 0xb1 ) {
            FILE *fp;
            char file_name[] = "routeXXXXXX";
            mkstemp(file_name);

            fp = fopen(file_name, "w");

            // 入力が尽きるまで読み取り続ける
            while( recv(clitSock, recvBuffer, BUFSIZE, 0) > 0 ) {
                fprintf(fp, "%s", recvBuffer);
            }

            fclose(fp);
            saved_route_update(user_id, route_id, &file_name[0]);
        }
        memset(&recvBuffer, 0, sizeof(recvBuffer));
        memset(&sendBuffer, 0, sizeof(sendBuffer));
        printf("next data ...\n");
    }

    printf("closed\n");
    close(clitSock);
}


int main() {
    pthread_t a;

    int errnu;

    memset(&servSockAddr, 0, sizeof(servSockAddr));
    servSockAddr.sin_family      = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port        = htons(servPort);

    pthread_detach(pthread_self());

    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        pthread_exit(&servSock);
    }

    if (( errnu = bind(servSock, (struct sockaddr *) &servSockAddr, sizeof(servSockAddr)) ) < 0 ) {
        perror("bind() failed.");
        pthread_exit(&errnu);
    }

    if (( errnu = listen(servSock, QUEUELIMIT) ) < 0) {
        perror("listen() failed.");
        pthread_exit(&errnu);
    }

    while(1) {
        clitLen = sizeof(clitSockAddr);
        printf("Waiting for connecting ...\n");
        if ((clitSock = accept(servSock, (struct sockaddr *) &clitSockAddr, &clitLen)) < 0) {
            perror("accept() failed.");
            pthread_exit(&clitLen);
        }

        int pid = fork();
        if(pid == 0) {
            close(servSock);
            conn_process();
            exit(0);
        } else {
            int stat; pid_t wpid;
            close(clitSock);
            while( (wpid = waitpid(-1, &stat, WNOHANG)) >= 0 ) {

            }
        }
        continue;
    }
}
