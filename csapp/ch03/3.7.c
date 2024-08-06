#include <stdio.h>

long scale2(long x, long y, long z)
{
    long t = x * 5 + y * 2 + z * 8;
    return t;
}

int main(void)
{
    long x = 10;
    long y = 20;
    long z = 30;

    printf("%ld\n", scale2(x, y, z));

    return 0;
}
