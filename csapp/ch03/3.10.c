#include <stdio.h>

long arith2(long x, long y, long z)
{
    long t1 = x | y;
    long t2 = t1 >> 3;
    long t3 = ~t2;
    long t4 = z - t3;

    return t4;
}

int main(void)
{
    long x = 11;
    long y = 22;
    long z = 33;

    printf("%ld\n", arith2(x, y, z));

    return 0;
}
