#include <stdio.h>

int div16(int x)
{
    return (x + (x >> 31 & 0xF)) >> 4;
}

int main(void)
{
    printf("%d\n", div16(32));
    printf("%d\n", div16(64));
    printf("%d\n", div16(100));

    return 0;
}
