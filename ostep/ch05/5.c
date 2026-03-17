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
        int rc = wait(NULL);
        printf("parent id: %d\n", getpid());
        printf("wait returns: %d\n", rc);
    } else if (rc == 0) {
        // child
        /* int rc = wait(NULL); */
        printf("child id: %d\n", getpid());
        /* printf("wait returns: %d\n", rc); */
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
