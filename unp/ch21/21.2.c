#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd;
    socklen_t salen;
    struct sockaddr *cli, *serv;

    if (argc != 2) {
        err_quit("usage: udpcli06 <IPaddress>");
    }

    sockfd = Udp_client(argv[1], "daytime", (void **)&serv, &salen);

    cli = Malloc(salen);
    memcpy(cli, serv, salen);
    sock_set_port(cli, salen, 0);
    Bind(sockfd, cli, salen);

    dg_cli(stdin, sockfd, serv, salen);

    return 0;
}
