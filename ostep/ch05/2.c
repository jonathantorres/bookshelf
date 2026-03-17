#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    int fd = open("./test.txt", O_RDWR);

    if (fd > 0) {
        int res = fork();
        if (res > 0) {
            char *buf = "parent";
            printf("fd in parent: %d\n", fd);
            write(fd, buf, strlen(buf));
        } else if (res == 0) {
            char *buf = "child";
            printf("fd in child: %d\n", fd);
            write(fd, buf, strlen(buf));
        } else {
            puts("fork failed");
            exit(1);
        }
    } else {
        puts("Could not open the file");
        exit(1);
    }

    return 0;
}
