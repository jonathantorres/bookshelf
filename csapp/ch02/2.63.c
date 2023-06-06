#include <stdio.h>

// performs a logical right shift
unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int)x >> k;
    int mask      = -1 + (1 << (sizeof(int) << 3) - k);

    return xsra & mask;
}

// performs an arithmetic right shift
int sra(int x, int k)
{
    int xsrl = (unsigned)x >> k;
    int mask = 1 << (sizeof(int) << 3) - k;

    mask &= x;

    return xsrl | mask;
}

int main(void)
{
    printf("%u\n", 10 >> 1);
    printf("%u\n", srl(10, 1));

    printf("%d\n", -5 >> 1);
    printf("%d\n", sra(-5, 1));

    return 0;
}
