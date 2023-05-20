#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int fildes[2];
    char *buf = "Jonathan Torres";
    pipe(fildes);
    pid_t rc = fork();
    if (rc > 0) {
        // parent
        puts("parent");
    } else if (rc == 0) {
        // child
        pid_t rc2 = fork();
        if (rc2 > 0) {
            close(fildes[0]);
            write(fildes[1], buf, strlen(buf));
            close(fildes[1]);
            puts("child");
            exit(0);
        } else if (rc2 == 0) {
            puts("child of child");
            close(fildes[1]);
            char bufbuf[100];
            read(fildes[0], bufbuf, 100);
            printf("%s\n", bufbuf);
            close(fildes[0]);
            exit(0);
        }
    } else {
        puts("fork() has failed!");
        exit(1);
    }
    return 0;
}
