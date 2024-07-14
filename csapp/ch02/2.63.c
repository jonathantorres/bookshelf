#include <stdio.h>

unsigned srl(unsigned x, int k)
{
    /* perform shift arithmetically */
    unsigned xsra = (int)x >> k;
    int w         = sizeof(int) * 8;
    unsigned l    = (0x1 << (w - 1));

    // if msb of x is 1
    // then the leftmost k bits of xsra must be 0
    if (k > 0 && x & l) {
        unsigned m = ~(~0U << (w - k));
        return xsra & m;
    }

    return xsra;
}

int sra(int x, int k)
{
    /* perform shift logically */
    int xsrl   = (unsigned)x >> k;
    int w      = sizeof(int) * 8;
    unsigned l = (0x1 << (w - 1));

    // if msb of x is 1
    // then the leftmost k bits of xsrl must be 1
    if (k > 0 && x & l) {
        unsigned m = ~0U << (w - k);

        return xsrl | m;
    }

    return xsrl;
}

int main(void)
{
    printf("0x%X\n", srl(~0U, 0));
    printf("0x%X\n", sra(~0, 0));

    printf("0x%X\n", srl(~0U, 1));
    printf("0x%X\n", sra(~0, 1));

    return 0;
}
