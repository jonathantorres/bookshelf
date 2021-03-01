#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <strings.h>
#include    <unistd.h>
#include    <signal.h>
#include    <sys/stat.h>
#include    <sys/param.h>
#include    <sys/types.h>
#include    <sys/wait.h>
#include    <errno.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <netinet/tcp.h>
#include    <arpa/inet.h>

#define SERV_TCP_PORT   6000
#define SERV_HOST_ADDR  "localhost"

char *pname;
extern int errno;

int main(int argc, char **argv)
{
    int sockfd, newsockfd, childpid;
    unsigned int clilen;
    struct sockaddr_in cli_addr, serv_addr;
    char msg[1000];
    int maxseg;
    unsigned int maxseg_s = sizeof(maxseg);

    pname = argv[0];

    /*
     * Open a TCP socket (an Internet stream socket).
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("server: can't open stream socket");
        exit(1);
    }

    /*
     * Bind our local address so that the client can send to us.
     */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(SERV_TCP_PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("server: can't bind local address");
        exit(1);
    }

    listen(sockfd, 5);

    for ( ; ; ) {
        /*
         * Wait for a connection from a client process.
         * This is an example of a concurrent server.
         */
        clilen = (unsigned int)sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("server: accept error");
            exit(1);
        }

        if ((childpid = fork()) < 0) {
            perror("server: fork error");
            exit(1);
        } else if (childpid == 0) {   /* child process */
            close(sockfd);      /* close original socket */
            int v = getsockopt(newsockfd, IPPROTO_TCP, TCP_MAXSEG, &maxseg, &maxseg_s);
            if (v < 0) {
                perror("getsockopt error: ");
            }
            sprintf(msg, "TCP_MAXSEG is %d\n", maxseg);
            write(newsockfd, msg, strlen(msg));
            exit(0);
        }

        close(newsockfd);       /* parent process */
    }
    return 0;
}
