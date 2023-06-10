#include <stdio.h>

// return 1 when x can be represented
// as an n-bit, 2's complement value
int fit_bits(int x, int n)
{
    int y         = x;
    unsigned low  = ~0 << (n - 1);
    unsigned high = ~low;

    y |= y >> 16;
    y |= y >> 8;
    y |= y >> 4;
    y |= y >> 2;
    y |= y >> 1;
    y = y ^ (y >> 0x01);

    return (y & high) != 0 || (x & low) == low;
}

int main(void)
{
    printf("%d\n", fit_bits(4, 4));     // 1
    printf("%d\n", fit_bits(500, 8));   // 0
    printf("%d\n", fit_bits(1500, 16)); // 1
    printf("%d\n", fit_bits(500, 32));  // 1
    printf("%d\n", fit_bits(-10, 4));   // 0
    printf("%d\n", fit_bits(-128, 8));  // 1
    printf("%d\n", fit_bits(-129, 8));  // 0

    return 0;
}
