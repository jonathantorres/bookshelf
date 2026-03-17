#include "apue.h"

#define BUFFSIZE 150000000

void handler(int signo)
{
    puts("signal caught");
}

int main(void)
{
    FILE *f = fopen("sync.txt", "w");

    if (!f) {
        err_sys("fopen error");
    }

    signal(SIGALRM, handler);

    alarm(1);

    char *buf = malloc(BUFFSIZE);

    if (!buf) {
        err_sys("malloc error");
    }

    fwrite(buf, sizeof(buf), 1, f);
    fclose(f);

    return 0;
}
