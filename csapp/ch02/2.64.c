#include <stdio.h>

int any_odd_one(unsigned x)
{
    unsigned m = 0xAAAAAAAA;

    return (x & m) != 0;
}

int main(void)
{
    printf("%d\n", any_odd_one(0x2));  // 1
    printf("%d\n", any_odd_one(0xC));  // 1
    printf("%d\n", any_odd_one(0x9));  // 1
    printf("%d\n", any_odd_one(0x7));  // 1
    printf("%d\n", any_odd_one(0x54)); // 0
    printf("%d\n", any_odd_one(0x0));  // 0
    printf("%d\n", any_odd_one(0x1));  // 0
    printf("%d\n", any_odd_one(0x4));  // 0
    printf("%d\n", any_odd_one(0x5));  // 0

    return 0;
}
