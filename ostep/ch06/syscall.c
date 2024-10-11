#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    int fd = open("./syscall.c", 0);
    char buf[0];

    if (fd < 0) {
        perror("open error");
        exit(1);
    }

    clock_t t1 = clock();
    int runs   = 1000000;

    for (int i = 0; i < runs; ++i) {
        read(fd, buf, 0);
    }

    clock_t t2      = clock();
    double duration = (1000000.0 * (t2 - t1) / CLOCKS_PER_SEC) / (double)runs;

    printf("results: %.5f μs\n", duration);
    close(fd);

    return 0;
}
