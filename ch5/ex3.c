#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
        sleep(1);
        puts("goodbye");
    } else if (rc == 0) {
        // child
        puts("hello");
    } else {
        puts("fork() has failed!");
        exit(1);
    }

    return 0;
}
