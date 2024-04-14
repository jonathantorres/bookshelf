#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define MAXLINE        512
#define SERV_TCP_PORT  6000
#define SERV_HOST_ADDR "localhost"

void str_echo(int sockfd);
int readline(int fd, char *ptr, int maxlen);

int main(void)
{
    int sockfd, newsockfd;
    unsigned int clilen;
    struct sockaddr_in cli_addr, serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("server: can't open stream socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(SERV_TCP_PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("server: can't bind local address");
        exit(1);
    }

    listen(sockfd, 1000);

    for ( ; ; ) {
        clilen = (unsigned int)sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("server: accept error");
            exit(1);
        }
        str_echo(newsockfd);
        close(newsockfd);
    }
    close(sockfd);
    return 0;
}

void str_echo(int sockfd)
{
    int n;
    char line[MAXLINE];

    for ( ; ; ) {
        n = readline(sockfd, line, MAXLINE);
        if (n == 0) {
            return;     /* connection terminated */
        } else if (n < 0) {
            perror("str_echo: readline error");
            exit(1);
        }

        printf("Got: %s", line);
    }
}

int readline(int fd, char *ptr, int maxlen)
{
    int n, rc;
    char c;

    for (n = 1; n < maxlen; n++) {
        if ((rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            if (n == 1) {
                return 0;  /* EOF, no data read */
            } else {
                break;      /* EOF, some data was read */
            }
        } else {
            return -1; /* error */
        }
    }
    *ptr = 0;
    return n;
}
