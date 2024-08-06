#include <stdio.h>

long test(long x, long y, long z)
{
    long val = x + y + z;

    if (x < -3) {
        if (y < z) {
            val = x * y;
        } else {
            val = y * z;
        }
    } else if (x > 2) {
        val = x * z;
    }

    return val;
}

int main(void)
{
    long x = 20;
    long y = 25;
    long z = 50;

    printf("%ld\n", test(x, y, z));

    return 0;
}
