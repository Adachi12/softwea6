#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 1024
#define QUEUE_LIMIT 5

int main(int argc, char *argv[]) {
    int errno;
    int clitSock;                    // client socket descriptor
    struct sockaddr_in clitSockAddr; // client internet socket address
    unsigned int clitLen;            // client internet socket address length
    char recvBuffer[BUFSIZE];        // receive temporary buffer
    char sendBuffer[BUFSIZE];        // receive temporary buffer
    int recvMsgSize, sendMsgSize;    // recieve and send buffer size
    int servSock;                    // server socket descriptor
    struct sockaddr_in servSockAddr; // server internet socket address
    unsigned int servPort;   // Port number

    if ( argc != 2) {
        fprintf(stderr, "argument count mismatch error.\n");
        exit(EXIT_FAILURE);
    }

    if ((servPort = (unsigned short) atoi(argv[1])) == 0) {
        fprintf(stderr, "invalid port number.\n");
        exit(EXIT_FAILURE);
    }

    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    memset(&servSockAddr, 0, sizeof(servSockAddr));
    servSockAddr.sin_family      = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port        = htons(servPort);

    if ( socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) < 0 ){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    if ( bind(servSock, (struct sockaddr *) &servSockAddr, sizeof(servSockAddr)) < 0 ) {
        perror("bind() failed.");
        exit(EXIT_FAILURE);
    }

    if ( listen(servSock, QUEUE_LIMIT) < 0) {
        perror("listen() failed.");
        exit(EXIT_FAILURE);
    }
    

    while(1) {
        clitLen = sizeof(clitSockAddr);

        printf("Waiting for connecting for client ...\n");
        if ((clitSock = accept(servSock, (struct sockaddr *) &clitSockAddr, &clitLen)) < 0) {
            perror("accept() failed.");
            exit(EXIT_FAILURE);
        }

        printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

        while(1) {
            if ((recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0)) < 0) {
                perror("recv() failed.");
                exit(EXIT_FAILURE);
            } else if(recvMsgSize == 0){
                fprintf(stderr, "connection closed by foreign host.\n");
                break;
            }

            if((sendMsgSize = send(clitSock, recvBuffer, recvMsgSize, 0)) < 0){
                perror("send() failed.");
                exit(EXIT_FAILURE);
            } else if(sendMsgSize == 0){
                fprintf(stderr, "connection closed by foreign host.\n");
                break;
            }
        }

        close(clitSock);
    }

    return EXIT_SUCCESS;
}