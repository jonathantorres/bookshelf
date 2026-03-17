#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[])
{
    unsigned char xor = 0;
    unsigned char buff_a[BUFFSIZE];
    unsigned char buff_b = 0;
    int fda, fdb;
    int count = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s [filename] [checksum file name]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fda = open(argv[1], O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }
    if ((fdb = open(argv[2], O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fda, buff_a, BUFFSIZE)) != -1 && count != 0) {
        for (int i = 0; i < count; i++) {
            xor ^= buff_a[i];
        }

        if ((count = read(fdb, &buff_b, 1)) == -1) {
            perror("problem reading file");
            exit(EXIT_FAILURE);
        }
        if (xor != buff_b) {
            printf("ERROR! This file is corrupted!\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("This file is fine.\n");
    close(fda);
    close(fdb);
    return 0;
}
