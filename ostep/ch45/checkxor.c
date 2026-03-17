#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    unsigned char xor = 0;
    int fd;
    char buff[1] = "";
    ssize_t count = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fd, buff, 1)) != -1 && count != 0) {
        if (buff[0] != '\n') {
            xor ^= (buff[0] - '0');
        }
    }

    printf("XOR checksum: %d\n", xor);
    close(fd);
    return 0;
}
