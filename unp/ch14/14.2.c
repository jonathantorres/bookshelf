#include "unp.h"

static void connect_alarm(int);

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
    Sigfunc *sigfunc;
    int n;

    sigfunc = Signal(SIGALRM, connect_alarm);

    if (alarm(nsec) != 0) {
        err_msg("connect_timeo: alarm was already set");
    }

    if ((n = connect(sockfd, saptr, salen)) < 0) {
        close(sockfd);

        if (errno == EINTR) {
            errno = ETIMEDOUT;
        }
    }

    alarm(0);
    Signal(SIGALRM, sigfunc);

    return n;
}

static void connect_alarm(int signo)
{
    return;
}

int main(int argc, char **argv)
{
    int sockfd, n, counter = 0, nsec = 5;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: a.out <IPaddress>");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        err_quit("inet_pton error for %s", argv[1]);
    }

    if (connect_timeo(sockfd, (SA *)&servaddr, sizeof(servaddr), nsec) < 0) {
        err_sys("connect error");
    }

    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        counter++;
        recvline[n] = 0;

        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    printf("counter = %d\n", counter);

    return 0;
}
