#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    if (i < 0 || i > sizeof(unsigned) - 1) {
        return x;
    }

    unsigned mask = 0xFF << (i << 3);
    unsigned y    = b << (i << 3);

    return (x & ~mask) | y;
}

int main(void)
{
    printf("0x%X\n", replace_byte(0x12345678, 2, 0xAB)); // returns 0x12AB5678
    printf("0x%X\n", replace_byte(0x12345678, 0, 0xAB)); // returns 0x123456AB

    return 0;
}
