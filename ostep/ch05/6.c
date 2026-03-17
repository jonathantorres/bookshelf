#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
        int ret = waitpid(rc, NULL, 0);
        printf("parent id: %d\n", getpid());
        printf("wait returns: %d\n", ret);
    } else if (rc == 0) {
        // child
        printf("child id: %d\n", getpid());
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
