#include <stdio.h>

// return 1 when x contains an odd number of 1s, 0 otherwise
int odd_ones(unsigned x)
{
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;

    return x & 0x01;
}

int main(void)
{
    printf("%d\n", odd_ones(0x0)); // 0
    printf("%d\n", odd_ones(0x6)); // 0
    printf("%d\n", odd_ones(0x2)); // 1
    printf("%d\n", odd_ones(0xE)); // 1

    return 0;
}
