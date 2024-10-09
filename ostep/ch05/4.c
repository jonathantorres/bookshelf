#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
        int rc = execl("/bin/ls", "ls ~", (char *)0, (char *)0);
        if (rc < 0) {
            perror("exec on the parent error");
        }
    } else if (rc == 0) {
        // child
        char *argv[3];
        argv[0] = "ls";
        argv[1] = "/home/jonathan/dev";
        argv[2] = NULL;
        int rc  = execv("/bin/ls", argv);
        if (rc < 0) {
            perror("exec on the child error");
        }
    } else {
        puts("fork() has failed!");
        exit(1);
    }

    return 0;
}
