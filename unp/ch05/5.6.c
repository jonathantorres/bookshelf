#include "unp.h"

void sig_handler(int sig);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: tcpcli <IP>\n");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13); // daytime server

    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    // signal handling
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGPIPE, &sa, NULL) == -1) {
        err_sys("sigaction error");
    }

    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    sleep(2);

    if (write(sockfd, "hello", 5) == -1) {
        err_sys("write error");
    }

    sleep(2);

    if (write(sockfd, "world", 5) == -1) {
        err_sys("write2 error");
    }

    return 0;
}

void sig_handler(int sig)
{
    if (sig == SIGPIPE) {
        printf("SIGPIPE received\n");
    }
    return;
}
