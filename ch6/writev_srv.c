#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXMESG 2048
#define SERV_UDP_PORT 6000

char *pname;

void dg_echo(int sockfd, struct sockaddr *pcli_addr, int maxclilen);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;

    pname = argv[0];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("server: can't open datagram socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(SERV_UDP_PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("server: can't bind local address");
        exit(1);
    }

    dg_echo(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
}


void dg_echo(int sockfd, struct sockaddr *pcli_addr, int maxclilen)
{
    int n;
    unsigned int clilen;
    char mesg[MAXMESG];

    for ( ; ; ) {
        clilen = maxclilen;
        n = recvfrom(sockfd, mesg, MAXMESG, 0, pcli_addr, &clilen);
        if (n < 0) {
            perror("dg_echo: recvfrom error");
            exit(1);
        }

        if (sendto(sockfd, mesg, n, 0, pcli_addr, clilen) != n) {
            perror("dg_echo: sendto error");
            exit(1);
        }
    }
}
