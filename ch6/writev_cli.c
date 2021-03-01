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

#define MAXLINE 512
#define MAXMESG 2048
#define SERV_UDP_PORT 6000
#define SERV_HOST_ADDR "127.0.0.1"

char *pname;

void dg_cli(FILE *fp, int sockfd, struct sockaddr *pserv_addr, int servlen);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in cli_addr, serv_addr;

    pname = argv[0];

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port        = htons(SERV_UDP_PORT);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("client: can't open datagram socket");
        exit(1);
    }

    bzero((char *) &cli_addr, sizeof(cli_addr));
    cli_addr.sin_family      = AF_INET;
    cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    cli_addr.sin_port        = htons(0);
    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0) {
        perror("client: can't bind local address");
        exit(1);
    }

    dg_cli(stdin, sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    close(sockfd);
    return 0;
}


void dg_cli(FILE *fp, int sockfd, struct sockaddr *pserv_addr, int servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    struct iovec iov[1];
    int tmp;

    iov[0].iov_base = (char *)&sendline;
    iov[0].iov_len = MAXLINE;

    tmp = open("tmp.out", O_RDWR|O_CREAT);
    if (tmp < 0) {
        perror("error opening tmp file");
        exit(1);
    }

    while (fgets(sendline, MAXLINE, fp) != NULL) {
        n = strlen(sendline);
        if (writev(tmp, &iov[0], 1) < 0) {
            perror("dg_cli: writev error on tmp file");
            exit(1);
        }
        if (sendto(sockfd, iov[0].iov_base, iov[0].iov_len, 0, pserv_addr, servlen) < 0) {
            perror("dg_cli: sendto error on socket");
            exit(1);
        }

        n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *) 0, (unsigned int *) 0);
        if (n < 0) {
            perror("dg_cli: recvfrom error");
            exit(1);
        }
        recvline[n] = '\0';
        fputs(recvline, stdout);
    }

    if (ferror(fp)) {
        perror("dg_cli: error reading file");
        exit(1);
    }
}
