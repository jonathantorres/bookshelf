#include "unp.h"

void str_echo_io(int sockfd);

int main(void)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);

        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            str_echo_io(connfd);
            exit(0);
        }

        Close(connfd);
    }
}

void str_echo_io(int sockfd)
{
    char line[MAXLINE];
    FILE *fpin, *fpout;

    fpin  = Fdopen(sockfd, "r");
    fpout = Fdopen(sockfd, "w");

    while (Fgets(line, MAXLINE, fpin) != NULL) {
        Fputs(line, fpout);
        fflush(fpout);
    }
}
