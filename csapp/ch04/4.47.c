/* A = C Program Below */
#include <stdio.h>

void bubble_b(long *data, long count)
{
    long i, last;
    long *n = data;

    for (last = count - 1; last > 0; last--) {
        for (i = 0, n = data; i < last; i++, n++) {
            if (*(n + 1) < *n) {
                long t   = *(n + 1);
                *(n + 1) = *n;
                *n       = t;
            }
        }
    }
}

int main(void)
{
    long nums[] = {3, 4, 91, 32, 23, 11, 8};
    long *n     = nums;

    for (int i = 0; i < 7; i++) {
        printf("%d\n", *n);
        n++;
    }

    printf(" =======================\n");
    n = nums;
    bubble_b(nums, 7);

    for (int i = 0; i < 7; i++) {
        printf("%d\n", *n);
        n++;
    }

    return 0;
}
