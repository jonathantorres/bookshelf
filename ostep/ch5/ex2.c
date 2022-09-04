#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("./test.txt", O_RDWR);
    char *buf = "Jonathan";
    if (fd > 0) {
        int f_result = fork();
        if (f_result > 0) {
            printf("fd in parent: %d\n", fd);
            write(fd, buf, strlen(buf));
        } else if (f_result == 0) {
            printf("fd in child: %d\n", fd);
            write(fd, buf, strlen(buf));
        }
    } else {
        puts("Could not open the file");
        exit(1);
    }

    return 0;
}
