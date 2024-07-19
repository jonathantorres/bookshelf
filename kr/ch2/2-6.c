#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void)
{
    printf("0x%X\n", setbits(0x12345678, 15, 16, 0x0000ABCD)); // 0x1234ABCD
    printf("0x%X\n", setbits(0x12345678, 23, 16, 0x0000ABCD)); // 0x12ABCD78

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned r = getbits(y, n - 1, n);
    unsigned m = ~(~0U << n) << (p - n + 1);

    return (x & ~m) | (r << (p - n + 1));
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0U << n);
}
