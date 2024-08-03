#include <stdio.h>

int fits_bits(int x, int n)
{
    int y        = x;
    unsigned min = ~0U << (n - 1);
    unsigned max = ~min;

    y |= y >> 16;
    y |= y >> 8;
    y |= y >> 4;
    y |= y >> 2;
    y |= y >> 1;
    y = y ^ (y >> 0x01);

    return (y & max) != 0 || (x & min) == min;
}

int main(void)
{
    printf("%d\n", fits_bits(4, 4));     // 1
    printf("%d\n", fits_bits(-10, 4));   // 0
    printf("%d\n", fits_bits(500, 8));   // 0
    printf("%d\n", fits_bits(-129, 8));  // 0
    printf("%d\n", fits_bits(-128, 8));  // 1
    printf("%d\n", fits_bits(1500, 16)); // 1
    printf("%d\n", fits_bits(500, 32));  // 1

    return 0;
}
