#include "csapp.h"

int main(void)
{
    int n;
    rio_t rio;
    char buf[MAXBUF];

    while ((n = Rio_readn(STDIN_FILENO, buf, MAXBUF)) != 0) {
        Rio_writen(STDOUT_FILENO, buf, n);
    }

    return 0;
}
