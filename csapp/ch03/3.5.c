#include <stdio.h>

void decode1(long *xp, long *yp, long *zp)
{
    long x = *xp;
    long y = *yp;
    long z = *zp;

    *yp = x;
    *zp = y;
    *xp = z;
}

int main(void)
{
    long x = 1;
    long y = 2;
    long z = 3;

    printf("%ld - %ld - %ld\n", x, y, z);
    decode1(&x, &y, &z);
    printf("%ld - %ld - %ld\n", x, y, z);

    return 0;
}
