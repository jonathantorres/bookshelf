#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main(void)
{
    printf("0x%X\n", rightrot(0x12345678, 0));  // 0x12345678
    printf("0x%X\n", rightrot(0x12345678, 4));  // 0x82345671
    printf("0x%X\n", rightrot(0x12345678, 8));  // 0x78123456
    printf("0x%X\n", rightrot(0x12345678, 16)); // 0x56781234
    printf("0x%X\n", rightrot(0x12345678, 32)); // 0x12345678
    printf("0x%X\n", rightrot(0x6, 1));         // 0x3

    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    int s = sizeof(x) << 3;

    return x >> n | x << (s - n);
}
