#include <stdio.h>

long decode(long x, long y, long z)
{
    y -= z;
    return (y << 63 >> 63) ^ (x * y);
}

int main(void)
{
    long x = 15;
    long y = 25;
    long z = 35;

    printf("%ld\n", decode(x, y, z));

    return 0;
}
