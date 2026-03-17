#include "apue.h"

// program to illustrate the creation of a zombie process

#define PS "ps -o pid,ppid,state,tty,command"

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_quit("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // this is the child
        exit(EXIT_SUCCESS);
    }

    // parent
    sleep(4);
    system(PS);

    return 0;
}
