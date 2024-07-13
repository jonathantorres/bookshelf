#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    int s = i << 3;
    return (x & ~(0xFF << s)) | (b << s);
}

int main(void)
{
    printf("0x%X\n", replace_byte(0x12345678, 2, 0xAB));
    printf("0x%X\n", replace_byte(0x12345678, 0, 0xAB));

    return 0;
}
