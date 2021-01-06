#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

int main() {
    int sockfd, nbytes;
    char buf[BUFSIZ];
    char *mesg = "ab";
    struct sockaddr_in servaddr;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7);
    
    if(inet_pton(AF_INET, "54.90.205.238", &servaddr.sin_addr) < 0) {
        perror("inet_pton");
        return 1;
    }
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("conneect");
        return 1;
    }

    nbytes = write(sockfd, mesg, strlen(mesg));
    close(sockfd);

    return 0;
}