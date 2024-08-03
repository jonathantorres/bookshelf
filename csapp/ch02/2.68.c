#include <stdio.h>

int lower_one_mask(int n)
{
    unsigned w = sizeof(int) << 3;

    return ~0U >> (w - n);
}

int main(void)
{
    printf("0x%X\n", lower_one_mask(1));  // 0x1
    printf("0x%X\n", lower_one_mask(6));  // 0x3F
    printf("0x%X\n", lower_one_mask(17)); // 0x1FFFF
    printf("0x%X\n", lower_one_mask(32)); // 0xFFFFFFFF

    return 0;
}
