#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "common.h"

#define POLY 0x1021

int main(int argc, char *argv[])
{
    unsigned short crc = 0xffff;
    unsigned short buff[1];
    int i = 0, xor_flag = 0, fd, count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("problem opening file");
        exit(EXIT_FAILURE);
    }

    while ((count = read(fd, buff, 1)) != -1 && count != 0) {
        unsigned short v = 0x80;
        for (size_t j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                xor_flag = 1;
            } else {
                xor_flag = 0;
            }
            crc = crc << 1;
            if (buff[0] & v) {
                crc += 1;
            }
            if (xor_flag) {
                crc = crc ^ POLY;
            }
            v = v >> 1;
        }
        i++;
    }

    for (size_t j = 0; j < 16; j++) {
        if (crc & 0x8000) {
            xor_flag = 1;
        } else {
            xor_flag = 0;
        }
        crc = crc << 1;
        if (xor_flag) {
            crc = crc ^ POLY;
        }
    }

    printf("16 bit crc: 0x%X\n", crc);
    close(fd);
    return 0;
}
