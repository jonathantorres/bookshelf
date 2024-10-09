#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
    } else if (rc == 0) {
        // child
        close(STDOUT_FILENO);
        int ret = printf("ok\n");
        fprintf(stderr, "%d\n", ret);
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
