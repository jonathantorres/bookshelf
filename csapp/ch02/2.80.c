#include <limits.h>
#include <stdio.h>

int threefourths(int x)
{
    int div4 = (x & ~0x3) >> 2;
    int mul3 = ((x & 0x3) << 1) + (x & 0x3);
    int bias = (1 << 2) - 1;

    ((x & INT_MIN) && (mul3 += bias));

    return (div4 << 1) + div4 + (mul3 >> 2);
}

int main(void)
{
    printf("%d\n", threefourths(100));
    printf("%d\n", threefourths(1000));
    printf("%d\n", threefourths(500));

    return 0;
}
