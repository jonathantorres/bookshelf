#include <stdio.h>

unsigned rotate_left(unsigned x, int n)
{
    unsigned w = sizeof(int) << 3;
    unsigned m = ~0 >> (w - n);

    return x << n | ((x >> (w - n)) & m);
}

int main(void)
{
    printf("0x%X\n", rotate_left(0x12345678, 4));  // 0x23456781
    printf("0x%X\n", rotate_left(0x12345678, 20)); // 0x67812345
    printf("0x%X\n", rotate_left(0x12345678, 32)); // 0x12345678
    printf("0x%X\n", rotate_left(0x12345678, 0));  // 0x12345678

    return 0;
}
