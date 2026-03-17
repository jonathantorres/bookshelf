#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[])
{
    unsigned char xor = 0;
    unsigned char buff[BUFFSIZE];
    int fdr, fdw;
    int count = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s [filename] [checksum file name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fdr = open(argv[1], O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }
    if ((fdw = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fdr, buff, BUFFSIZE)) != -1 && count != 0) {
        for (int i = 0; i < count; i++) {
            xor ^= buff[i];
        }

        if (write(fdw, &xor, 1) == -1) {
            perror("error writing to file");
            exit(EXIT_FAILURE);
        }
    }

    close(fdr);
    close(fdw);

    return 0;
}
