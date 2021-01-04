#include<stdio.h>
#include<unistd.h>
#include<strings.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"DB/src/jogging.h" 

int flag = 1;

void *conn_process(void *arg) {
    int listendfd, connfd, data_size;
    char req_op;
    char buf[BUFSIZ];
    struct sockaddr_in servaddr;

    if( (listendfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket");
        exit(1);
    }

    memset( &servaddr, 0, sizeof(servaddr) );

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(listendfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 ) {
        perror("listen");
        exit(1);
    }

    if( listen(listendfd, 5) < 0 ) {
        perror("listen");
        exit(1);
    } 

    while(1) {
        if ( (connfd = accept(listendfd, (struct sockaddr*)NULL, NULL)) < 0 ) {
            perror("accept");
            exit(1);
        }

        // フラグをもとに戻す
        flag = 1;

        // アクセス内容(1byte)を読み取る
        read(connfd, buf, 1);

        req_op = buf[0];

        // 分岐
        if ( req_op == 0x00 ) {
            // CALORIE_TABLE access
            CALORIE_TABLE resp_data = calorie_select();
            char *resp_bytes[BUFSIZ];
            if ( calorie_cast(&resp_bytes, resp_data) ) {
                perror("Error - CALORIE_TABLE Access\n");
                buf[0] = 0x01;
                write(connfd, buf, 1);
            }
            snprintf(buf, 260, "%s", resp_data);
            printf("%s\n", buf);
            write(connfd, buf, 260);
        }

        close(connfd);
    }

    pthread_exit(0);
}

int main() {
    pthread_t a;
    while(1) {
        pthread_create(&a, NULL, conn_process, NULL);
        
        while(flag == 0) ;

        printf("pthread:main\n");
        flag = 0;
        continue;
    }
}