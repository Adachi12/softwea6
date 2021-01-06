#include <stdio.h> //printf(), fprintf(), perror()
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset()
#include <unistd.h> //close()
#include <pthread.h> // pthread_create()
#include "DB/src/jogging.h"

#define QUEUELIMIT 5
#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)

int flag = 0;

int servSock; //server socket descriptor
struct sockaddr_in servSockAddr; //server internet socket address
unsigned int servPort = 60000;


void *conn_process() {
    int op;       // client request
    int clitSock; // client socket descriptor
    struct sockaddr_in clitSockAddr; // client internet socket address
    unsigned int clitLen;            // client internet socket address length
    char recvBuffer[BUFSIZE];        // receive temporary buffer
    char sendBuffer[BUFSIZE];        // receive temporary buffer
    int recvMsgSize, sendMsgSize;    // recieve and send buffer size


    while(1) {
        clitLen = sizeof(clitSockAddr);
        if ((clitSock = accept(servSock, (struct sockaddr *) &clitSockAddr, &clitLen)) < 0) {
            perror("accept() failed.");
            pthread_exit(&clitLen);
        }
        flag = 1;
        printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

        while(1) {
            // ルート保存用変数
            int user_id = 0, route_id = 0;
            // ルート取り出し用変数
            SAVED_ROUTE_TABLE resp_data;
            FILE *fp;
            // レシーブバッファ初期化
            memset(&recvBuffer, 0, sizeof(recvBuffer));

            // データ受け取り
            if ((recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0)) < 0) {
                perror("recv() failed.");
                pthread_exit(&recvMsgSize);
            } else if(recvMsgSize == 0){
                fprintf(stderr, "connection closed by foreign host.\n");
                break;
            }

            // ヘッダ確認・処理分岐
            op = recvBuffer[0];
            if ( op == 0x00 ) {
                // CALORIE_TABLE select
                CALORIE_TABLE resp_data = calorie_select();
                ct_tab2str_select(&sendBuffer, resp_data);
            } else if ( op == 0x10 ) {
                // SAVED_ROUTE_TABLE select
                sscanf(&recvBuffer, "%d\n%d\n%d", &op, &user_id, &route_id);
                fp = saved_route_select(user_id);
            } else if ( op == 0x11 ) {
                // SAVED_ROUTE_TABLE update
                int errno;
                sscanf(recvBuffer, "%d\n%d\n%d", &op, &user_id, &route_id);
            } else if ( op == 0x20 ) {
                // USEDLOG_TABLE select
                USEDLOG_TABLE resp_data;

                sscanf(&recvBuffer, "%d\n%d", &op, &user_id);
                resp_data = usedlog_select(id);
                ult_tab2str_select(&sendBuffer, resp_data);
            } else if ( op == 0x22 ) {
                // USEDLOG_TABLE insert
                int errno;
                USEDLOG_TABLE recv_data;

                recv_data = ult_str2tab_insert(recvBuffer);
                errno = usedlog_insert(recv_data);
                sprintf(sendBuffer, "%d", errno);
            } else if ( op == 0x30 ) {
                // USER_TABLE select
                USER_TABLE resp_data;

                sscanf(&recvBuffer, "%d\n%d", &op, &user_id);
                resp_data = user_select(user_id);
                ut_tab2str_select(&sendBuffer, resp_data);
            } else if ( op == 0x31 ) {
                // USER_TABLE update
                int errno;
                USER_TABLE recv_data;

                recv_data = ut_str2tab_update(recv_data, recvBuffer);
                errno = user_update(recv_data);
                sprintf(sendBuffer, "%d", errno);
            } else if ( op == 0x32 ) {
                // USER_TABLE insert
                int errno;
                USER_TABLE recv_data;

                recv_data = ut_str2tab_insert(recv_data, recvBuffer);
                errno = user_insert(recv_data);
                sprintf(sendBuffer, "%d", errno);
            }

            // 返信データ送信
            if ( op != 0x10 || 0x11 ) {
                if((sendMsgSize = send(clitSock, sendBuffer, BUFSIZE, 0)) < 0){
                    perror("send() failed.");
                    pthread_exit(&sendMsgSize);
                } else if(sendMsgSize == 0){
                    fprintf(stderr, "connection closed by foreign host.\n");
                    break;
                }
            }

            // ファイル送信モード
            if ( op == 0x10 ) {
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
            if ( op == 0x11 ) {
                FILE *fp;
                char file_name[] = "routeXXXXXX";
                mkstemp(&file_name);

                fp = fopen(file_name, "w");

                // 入力が尽きるまで読み取り続ける
                while( recv(clitSock, recvBuffer, BUFSIZE, 0) > 0 ) {
                    fprintf(fp, "%s", recvBuffer);
                }

                fclose(fp);
                saved_route_update(user_id, route_id, &file_name);
            }
        }

        close(clitSock);
    }

    close(servSock);

    pthread_exit(0);
}



int main() {
    pthread_t a;

    int errno; 

    memset(&servSockAddr, 0, sizeof(servSockAddr));
    servSockAddr.sin_family      = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port        = htons(servPort);

    pthread_detach(pthread_self());

    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        pthread_exit(&servSock);
    }

    if (( errno = bind(servSock, (struct sockaddr *) &servSockAddr, sizeof(servSockAddr)) ) < 0 ) {
        perror("bind() failed.");
        pthread_exit(&errno);
    }

    if (( errno = listen(servSock, QUEUELIMIT) ) < 0) {
        perror("listen() failed.");
        pthread_exit(&errno);
    }

    while(1) {
        pthread_create(&a, NULL, &conn_process, NULL);

        while(flag == 0) ;

        printf("pthread:main\n");
        flag = 0;
        continue;
    }
}

