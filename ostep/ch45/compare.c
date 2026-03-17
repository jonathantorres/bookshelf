#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

void run_xor(const char *file);
void run_fletcher(const char *file);

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    run_xor(argv[1]);
    run_fletcher(argv[1]);
    return 0;
}

void run_xor(const char *file)
{
    double time_s = time_get_seconds();
    ssize_t count = 0;
    unsigned char xor = 0;
    char buff[1] = "";
    int fd;

    if ((fd = open(file, O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fd, buff, 1)) != -1 && count != 0) {
        if (buff[0] != '\n') {
            xor ^= (buff[0] - '0');
        }
    }

    printf("XOR checksum: %d\n", xor);
    printf("XOR ran in: %f\n", time_get_seconds() - time_s);
    close(fd);
}

void run_fletcher(const char *file)
{
    double time_s = time_get_seconds();
    int fletcher_1 = 0, fletcher_2 = 0;
    char buff[1] = "";
    ssize_t count = 0;
    int fd;

    if ((fd = open(file, O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fd, buff, 1)) != -1 && count != 0) {
        if (buff[0] != '\n') {
            fletcher_1 = (buff[0] - '0' + fletcher_1) % 255;
            fletcher_2 = (fletcher_1 + fletcher_2) % 255;
        }
    }

    printf("Fletcher checksum: (%d, %d)\n", fletcher_1, fletcher_2);
    printf("Fletcher ran in: %f\n", time_get_seconds() - time_s);
    close(fd);
}
