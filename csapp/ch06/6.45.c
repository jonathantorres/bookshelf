#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLOCK_SIZE 16

void transpose(int *dst, int *src, int dim)
{
    int i, j, a, b;

    for (i = 0; i <= dim - BLOCK_SIZE; i += BLOCK_SIZE) {
        for (j = 0; j <= dim - BLOCK_SIZE; j += BLOCK_SIZE) {
            for (a = i; a < i + BLOCK_SIZE; a++) {
                for (b = j; b < j + BLOCK_SIZE; b++) {
                    dst[b * dim + a] = src[a * dim + b];
                }
            }
        }
    }

    int offset = i;

    for (i = offset; i <= dim - 1; i++) {
        for (j = 0; j < offset; j += BLOCK_SIZE) {
            for (b = j; b < j + BLOCK_SIZE; b++) {
                dst[b * dim + i] = src[i * dim + b];
            }
        }
    }

    for (i = 0; i <= dim - 1; i++) {
        for (j = offset; j <= dim - 1; j++) {
            dst[j * dim + i] = src[i * dim + j];
        }
    }
}

int main(void)
{
    int a[BLOCK_SIZE][BLOCK_SIZE] = {0};
    int b[BLOCK_SIZE][BLOCK_SIZE] = {0};

    srand(time(0));

    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            b[i][j] = rand();
        }
    }

    transpose((int *)a, (int *)b, BLOCK_SIZE);

    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%d ", a[i][j]);
        }

        printf("\n");
    }

    return 0;
}
