#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n, npend;
    char recvline[MAXLINE + 1];
    socklen_t len;
    struct sockaddr_storage ss;

    if (argc != 3) {
        err_quit("usage: daytimetcpcli <hostname/IPaddress> <service/port#>");
    }

    sockfd = Tcp_connect(argv[1], argv[2]);

    len = sizeof(ss);
    Getpeername(sockfd, (SA *)&ss, &len);
    printf("connected to %s\n", Sock_ntop_host((SA *)&ss, len));

    while (1) {
        if ((n = Recv(sockfd, recvline, MAXLINE, MSG_PEEK)) == 0) {
            break;
        }

        Ioctl(sockfd, FIONREAD, &npend);
        printf("%d bytes from PEEK, %d bytes pending\n", n, npend);

        n           = Read(sockfd, recvline, MAXLINE);
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }

    return 0;
}
