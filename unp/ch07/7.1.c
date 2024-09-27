#include "unp.h"
#include <netinet/tcp.h> /* for TCP_MAXSEG */

int main(void)
{
    int sockfd, rcvbuf, sndbuf;
    socklen_t len;

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    len = sizeof(rcvbuf);
    Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);

    len = sizeof(sndbuf);
    Getsockopt(sockfd, IPPROTO_TCP, SO_SNDBUF, &sndbuf, &len);

    printf("defaults: SO_RCVBUF = %d, SO_SNDBUF = %d\n", rcvbuf, sndbuf);

    return 0;
}
