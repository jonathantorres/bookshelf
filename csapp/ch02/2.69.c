#include <stdio.h>

unsigned rotate_left(unsigned x, int n)
{
    unsigned y = x;

    x <<= n;
    y >>= (sizeof(int) << 3) - n;

    return x | y;
}

int main(void)
{
    printf("%#x\n", rotate_left(0x12345678, 4));
    printf("%#x\n", rotate_left(0x12345678, 20));
    printf("%#x\n", rotate_left(0x12345678, 0));

    return 0;
}
