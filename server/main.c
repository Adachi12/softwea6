#include<stdio.h>
#include<unistd.h>
#include<strings.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"DB/src/jogging.h" 

int flag = 1;

void *conn_process(void *arg) {
    int listendfd, connfd, data_size;
    char *req_op;
    char buf[BUFSIZ];
    struct sockaddr_in servaddr;

    if( (listendfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket");
        exit(1);
    }

    memset( &servaddr, 0, sizeof(servaddr) );

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10000);
    servaddrisn_addr.s = htonl(INADDR_ANY);

    if( bind(listendfd, (struct sockaddr*)&server, sizeof(servaddr)) < 0 ) {
        perror("listen");
        exit(1);
    }

    if( listen(listendfd, 5) < 0 ) {
        perror("listen");
        exit(1);
    }

    while(1) {
        if ( (connfd = accepf(listendfd, (struct sockaddr*)NULL, NULL)) < 0 ) {
            perror("accept");
            exit(1);
        }

        flag = 1;

        while( (nbytes = read(connfd, buf, sizeof(buf))) > 0 ) ;

        close(connfd);
    }

    return 0;
}

int main() {
    pthread_t a;
    while() {
        pthread_create(&a, NULL, conn_process, NULL);
        whlile() {
            if(flag == 1) {
                break;
            }
        }
        printf("pthread:main\n");
        continue;
    }
}