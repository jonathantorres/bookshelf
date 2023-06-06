#include <stdio.h>

// generate mask indicating leftmost 1 in x, assume w = 32
int leftmost_one(unsigned x)
{
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;

    return x ^ (x >> 0x01);
}

int main(void)
{
    printf("%#x\n", leftmost_one(0xFF00)); // 0x8000
    printf("%#x\n", leftmost_one(0x6600)); // 0x4000

    return 0;
}
