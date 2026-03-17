#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fildes[2];

    if (pipe(fildes) < 0) {
        puts("error creating pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 > 0) {
        // parent
        wait(NULL);

        pid_t pid2 = fork();

        if (pid2 > 0) {
            // parent
            wait(NULL);
        } else if (pid2 == 0) {
            // second child
            close(fildes[1]);
            dup2(fildes[0], STDIN_FILENO);
            char buf[100];
            read(STDIN_FILENO, buf, 100);
            printf("child 2 read: \"%s\"\n", buf);
        } else {
            puts("second fork() has failed!");
            exit(1);
        }
    } else if (pid1 == 0) {
        // child
        close(fildes[0]);
        dup2(fildes[1], STDOUT_FILENO);
        printf("hi, from the first child");
    } else {
        puts("fork() has failed!");
        exit(1);
    }

    return 0;
}
