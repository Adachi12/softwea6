#include <stdio.h> //printf(), fprintf(), perror()
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa(), inet_aton()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset(), strcmp()
#include <unistd.h> //close()

#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)

int main() {

    int sock;                       //local socket descriptor
    struct sockaddr_in servSockAddr;//server internet socket address
    unsigned short servPort = 60000; //server port number
    char recvBuffer[BUFSIZE];       //receive temporary buffer
    char sendBuffer[BUFSIZE];       // send temporary buffer

    memset(&servSockAddr, 0, sizeof(servSockAddr));

    servSockAddr.sin_family = AF_INET;

    if (inet_aton("54.90.205.238", &servSockAddr.sin_addr) == 0) {
        fprintf(stderr, "Invalid IP Address.\n");
        exit(EXIT_FAILURE);
    }
    servSockAddr.sin_port = htons(servPort);

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*) &servSockAddr, sizeof(servSockAddr)) < 0) {
        perror("connect() failed.");
        exit(EXIT_FAILURE);
    }

    printf("connect to %s\n", inet_ntoa(servSockAddr.sin_addr));

    while(1) {
        printf("please enter the characters:");
        if (fgets(sendBuffer, BUFSIZE, stdin) == NULL){
            fprintf(stderr, "invalid input string.\n");
            exit(EXIT_FAILURE);
        }

        if (send(sock, sendBuffer, strlen(sendBuffer), 0) <= 0) {
            perror("send() failed.");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

long int getFileSize(const char* fileName)
{
    FILE* fp = fopen(fileName, "rb");
    if (fp == NULL) {
        return 0;
    }

    if (fseek(fp, 0L, SEEK_END) == 0) {
        fpos_t pos;

        if (fgetpos(fp, &pos) == 0) {
            fclose(fp);
            return (long int)pos;
        }
    }

    fclose(fp);
    return 0;
}