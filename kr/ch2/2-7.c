#include <stdio.h>

unsigned invert(unsigned x, int p, int n);
unsigned getbits(unsigned x, int p, int n);

int main(void)
{
    printf("0x%X\n", invert(0x12347777, 15, 16)); // 0x12348888
    printf("0x%X\n", invert(0x12777778, 23, 16)); // 0x12888878

    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned r = getbits(x, p, n);
    unsigned m = ~(~0U << n) << (p - n + 1);

    return (x & ~m) | (~r & ~(~0U << n)) << (p - n + 1);
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0U << n);
}
