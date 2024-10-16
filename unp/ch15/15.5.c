#include "unp.h"

int main(void)
{
    int sockfd;
    struct sockaddr_un cliaddr, servaddr;

    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sun_family = AF_LOCAL;
    strcpy(cliaddr.sun_path, tmpnam(NULL));

    Bind(sockfd, (SA *)&cliaddr, sizeof(cliaddr));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);

    dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));

    return 0;
}
