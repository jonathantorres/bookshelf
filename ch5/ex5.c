#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

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
        // int id = getppid();
        // int rc = wait(&id);
        printf("child id: %d\n", getpid());
        // printf("wait returns: %d\n", rc);
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
