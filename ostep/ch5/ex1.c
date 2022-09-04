#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int x = 100;
    pid_t rc = fork();

    if (rc > 0) {
        // parent
        printf("value of x in the parent: %d\n", x);
        x = 200;
        printf("value of x in the parent: %d\n", x);
    } else if (rc == 0) {
        // child
        printf("value of x in the child: %d\n", x);
        x = 300;
        printf("value of x in the child: %d\n", x);
    } else {
        puts("fork() has failed!");
        exit(1);
    }

    return 0;
}
