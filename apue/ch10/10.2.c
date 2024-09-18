#define _GNU_SOURCE 1

#include "apue.h"

int sig2str(int signo, char *str);

int main(void)
{
    char buf[MAXLINE];

    if (sig2str(SIGINT, buf) < 0) {
        err_sys("sig2str error");
    }

    printf("%s\n", buf);

    return 0;
}

int sig2str(int signo, char *str)
{
    char *s = NULL;

    if ((s = strsignal(signo)) == NULL) {
        return -1;
    }

    strcpy(str, s);

    return 0;
}
