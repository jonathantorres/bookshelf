#include <stdint.h>
#include <stdio.h>

int tmult_ok(int x, int y)
{
    int64_t p = (int64_t)x * y;

    return p == (int)p;
}

int main(void)
{
    printf("%d\n", tmult_ok(12500, 80));
    printf("%d\n", tmult_ok(50000000000, 80));
}
