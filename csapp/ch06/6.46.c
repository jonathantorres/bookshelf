#define BLOCK_SIZE 16

void col_convert(int *src, int dim)
{
    int i, j, a, b, tmp;

    for (i = 0; i <= dim - BLOCK_SIZE; i += BLOCK_SIZE) {
        for (j = i; j <= dim - BLOCK_SIZE; j += BLOCK_SIZE) {
            for (a = i; a < i + BLOCK_SIZE; a++) {
                for (b = j; b < j + BLOCK_SIZE; b++) {
                    tmp              = src[b * dim + a] || src[a * dim + b];
                    src[b * dim + a] = tmp;
                    src[a * dim + b] = tmp;
                }
            }
        }
    }

    int offset = i;

    for (i = offset; i <= dim - 1; i++) {
        for (j = 0; j < offset; j += BLOCK_SIZE) {
            for (b = j; b < j + BLOCK_SIZE; b++) {
                tmp              = src[b * dim + i] || src[i * dim + b];
                src[b * dim + i] = tmp;
                src[i * dim + b] = tmp;
            }
        }
    }

    for (i = offset; i <= dim - 1; i++) {
        for (j = i; j <= dim - 1; j++) {
            tmp              = src[j * dim + i] || src[i * dim + j];
            src[j * dim + i] = tmp;
            src[i * dim + j] = tmp;
        }
    }
}
