#include <stdio.h>

void merge(long src1[], long src2[], long dest[], long n)
{
    long i1 = 0;
    long i2 = 0;
    long id = 0;

    while (i1 < n && i2 < n) {
        dest[id++] = (src1[i1] < src2[i2]) ? src1[i1++] : src2[i2++];
    }

    while (i1 < n) {
        dest[id++] = src1[i1++];
    }

    while (i2 < n) {
        dest[id++] = src2[i2++];
    }
}

int main(void)
{
    long a[]   = {3, 5, 9, 8, 4, 1};
    long b[]   = {9, 1, 2, 7, 3, 8};
    long c[20] = {0};
    long *p    = c;

    merge(a, b, c, 6);

    while (1) {
        if (*p == 0) {
            break;
        }

        printf("%ld, ", *p++);
    }

    printf("\n");

    return 0;
}
