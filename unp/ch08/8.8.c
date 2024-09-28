#include "unp.h"

/* For an IPv4 socket, the largest amount we can send is 65,507 bytes of data,
 * with IPv6 we can send a bit less: 65,487 bytes. */

#define BUFSIZE 65507

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: udpcli <IPaddress>");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));

    return 0;
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int size;
    char sendline[BUFSIZE], recvline[BUFSIZE + 1];
    ssize_t n;

    size = 70000;
    Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

    Sendto(sockfd, sendline, BUFSIZE, 0, pservaddr, servlen);

    n = Recvfrom(sockfd, recvline, BUFSIZE, 0, NULL, NULL);

    printf("received %ld bytes\n", n);
}
