#include "csapp.h"

int echo_line(int connfd);
void command(void);

int main(int argc, char **argv)
{
    int listenfd, connfd, n;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    listenfd = Open_listenfd(argv[1]);
    n        = listenfd + 1;

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    while (1) {
        ready_set = read_set;
        Select(n, &ready_set, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &ready_set)) {
            command();
        }

        if (FD_ISSET(listenfd, &ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd    = Accept(listenfd, (SA *)&clientaddr, &clientlen);

            if (connfd + 1 > FD_SETSIZE) {
                fprintf(stderr, "too many clients\n");
                Close(connfd);
            }

            n = n > connfd + 1 ? n : connfd + 1;
            FD_SET(connfd, &read_set);
        }

        for (int fd = listenfd + 1; fd < n; fd++) {
            if (FD_ISSET(fd, &ready_set)) {
                if (echo_line(fd) == -1) {
                    Close(fd);
                    FD_CLR(fd, &read_set);
                }
            }
        }
    }
}

void command(void)
{
    char buf[MAXLINE];

    if (!Fgets(buf, MAXLINE, stdin)) {
        exit(0);
    }

    printf("%s", buf);
}

int echo_line(int connfd)
{
    ssize_t n;
    char buf[1];

    while ((n = Rio_readn(connfd, buf, 1)) > 0) {
        Rio_writen(connfd, buf, n);
        if (buf[0] = '\n') {
            return 0;
        }
    }
    return -1;
}
