#include "apue.h"

/* On Linux, this code triggers a segmentation fault */
/* because the stack frame in the parent is overriden */
/* with the zero bytes from the call to f2 in the child */

static void f1(void), f2(void);

int main(void)
{
    f1();
    f2();
    _exit(0);
}

static void f1(void)
{
    pid_t pid;

    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    }
    /* child and parent both return */
}

static void f2(void)
{
    char buf[1000];
    size_t i;

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = 0;
    }
}
