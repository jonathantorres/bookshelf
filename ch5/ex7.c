#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
    } else if (rc == 0) {
        // child
        close(STDOUT_FILENO);
        printf("ok\n");
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
