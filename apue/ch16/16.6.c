#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

int setasync(int sockfd);
int clrasync(int sockfd);

int main(void)
{
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (fd < 0) {
        err_sys("socket error");
    }

    if (setasync(fd) < 0) {
        err_sys("setasync error");
    }

    if (clrasync(fd) < 0) {
        err_sys("clrasync error");
    }

    return 0;
}

int setasync(int sockfd)
{
    int n;

    if (fcntl(sockfd, F_SETOWN, getpid()) < 0) {
        return -1;
    }

    n = 1;

    if (ioctl(sockfd, FIOASYNC, &n) < 0) {
        return -1;
    }

    return 0;
}

int clrasync(int sockfd)
{
    int n = 0;

    if (ioctl(sockfd, FIOASYNC, &n) < 0) {
        return -1;
    }

    return 0;
}
