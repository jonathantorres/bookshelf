#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define COUNT          20000
#define SERV_TCP_PORT  6000
#define SERV_HOST_ADDR "127.0.0.1"

int main(void)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    char *msg = "GET THIS!\n";

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port        = htons(SERV_TCP_PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("client: can't open tcp stream socket");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("client: can't connect to server");
        exit(1);
    }

    int rc;
    for (int i = 0; i < COUNT; i++) {
        if ((rc = write(sockfd, msg, strlen(msg))) < 0) {
            perror("write error");
            exit(1);
        }
        printf("wrote %d bytes\n", rc);
    }

    close(sockfd);
    return 0;
}
