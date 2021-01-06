#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>

int flag = 0;

void *conn_process(void *arg) {
    int listendfd, connfd;
    char buf[BUFSIZ];
    struct sockaddr_in servaddr;

    if( (listendfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket");
        pthread_exit(0);
    }

    memset( &servaddr, 0, sizeof(servaddr) );

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(listendfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 ) {
        perror("listen");
        pthread_exit(0);
    }

    if( listen(listendfd, 5) < 0 ) {
        perror("listen");
        pthread_exit(0);
    } 

    while(1) {
        if ( (connfd = accept(listendfd, (struct sockaddr*)NULL, NULL)) < 0 ) {
            perror("accept");
            pthread_exit(0);
        }

        // アクセス内容(1byte)を読み取る
        read(connfd, buf, 1);
        printf("%c", buf[0]);

        // アクセス内容(1byte)を読み取る
        read(connfd, buf, 1);
        printf("%c", buf[0]);

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