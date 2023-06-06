#include <stdio.h>

int lower_one_mask(int n)
{
    int m = ~0;
    m     = m << (n - 1) << 1;

    return m ^ ~0;
}

int main(void)
{
    printf("%X\n", lower_one_mask(6));
    printf("%X\n", lower_one_mask(17));
    printf("%X\n", lower_one_mask(32));

    return 0;
}
