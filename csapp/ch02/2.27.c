#include <stdio.h>

// determine whether arguments can be added without overflow
int uadd_ok(unsigned x, unsigned y)
{
    return (x + y) >= x;
}

int main(void)
{
    printf("%d\n", uadd_ok(550, 1000));
}
