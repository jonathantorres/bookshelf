#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
        int id = getpid();
        int rc = waitpid((pid_t)id, &id, WNOHANG);
        printf("parent id: %d\n", id);
        printf("wait returns: %d\n", rc);
    } else if (rc == 0) {
        // child
        printf("child id: %d\n", getpid());
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
