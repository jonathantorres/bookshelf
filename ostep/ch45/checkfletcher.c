#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd, fletcher_1 = 0, fletcher_2 = 0;
    char buff[1] = "";
    ssize_t count = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fd, buff, 1)) != -1 && count != 0) {
        if (buff[0] != '\n') {
            fletcher_1 = (buff[0] - '0' + fletcher_1) % 255;
            fletcher_2 = (fletcher_1 + fletcher_2) % 255;
        }
    }

    printf("Fletcher checksum: (%d, %d)\n", fletcher_1, fletcher_2);
    close(fd);
    return 0;
}
