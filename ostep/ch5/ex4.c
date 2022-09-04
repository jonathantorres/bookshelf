#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    pid_t rc = fork();
    if (rc > 0) {
        // parent
        int rc = execl("/bin/ls", "ls ~", (char*)0, (char*)0);
        if (rc < 0) {
            perror("parent error");
        }
    } else if (rc == 0) {
        // child
        int rc = execl("/bin/ls", "ls ~/dev", (char*)0, (char*)0);
        if (rc < 0) {
            perror("child error");
        }
    } else {
        puts("fork() has failed!");
        exit(1);
    }

    return 0;
}
