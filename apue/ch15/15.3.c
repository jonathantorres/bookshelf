#include "apue.h"

int main(void)
{
    char buf[MAXLINE];
    FILE *p = popen("foo", "r");

    if (!p) {
        err_sys("popen error");
    }

    pclose(p);

    return 0;
}
