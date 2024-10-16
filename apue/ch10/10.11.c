#include "apue.h"

#define BUFFSIZE 100

void handler(int signo)
{
    puts("signal handler");
}

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    signal(SIGXFSZ, handler);

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    return 0;
}
