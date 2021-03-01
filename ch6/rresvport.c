#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

extern int errno;

int rresvport(int *alport);

int main(void)
{
    int p;
    int rc = rresvport(&p);
    printf("fd=%d, port=%d\n", rc, p);
    return 0;
}

int rresvport(int *alport)
{
    struct sockaddr_in my_addr;
    int sockfd;

    bzero((char *) &my_addr, sizeof(my_addr));
    my_addr.sin_family      = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return-1;
    }

    for ( ; ; ) {
        my_addr.sin_port = htons(*alport);
        if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) >= 0) {
            break;      /* OK, all done */
        }

        if (errno != EADDRINUSE) {  /* some other error */
            close(sockfd);
            return(-1);
        }

        (*alport)--;    /* port already in use, try the next one */
        if (*alport == IPPORT_RESERVED / 2) {
            close(sockfd);
            errno = EAGAIN;
            return -1;
        }
    }
    return sockfd;
}
