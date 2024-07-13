#include <stdio.h>

int main(void)
{
    unsigned x = 0x89ABCDEF;
    unsigned y = 0x76543210;

    printf("0x%X\n", (x & 0xFF) | (y & ~0xFF));

    return 0;
}
