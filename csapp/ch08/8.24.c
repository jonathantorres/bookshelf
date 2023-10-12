#include "csapp.h"

int main()
{
    int status, i;
    pid_t pid;

    for (i = 0; i < 2; i++) {
        if ((pid = Fork()) == 0) {
            // cause segfault
            char *cptr = NULL;
            *cptr      = 'd';
        }
    }

    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            char buf[255];
            sprintf(buf, "child %d terminated by signal %d", pid, WTERMSIG(status));
            psignal(WTERMSIG(status), buf);
        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    if (errno != ECHILD) {
        unix_error("waitpid error");
    }

    return 0;
}
