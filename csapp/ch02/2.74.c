#include <limits.h>
#include <stdio.h>

// determine whether arguments can be subtracted without overflow
int tsub_ok(int x, int y)
{
    int sub = x - y;

    if (y == INT_MIN) {
        return 0;
    }

    return !(x > 0 && y < 0 && sub < 0) && !(x < 0 && y > 0 && sub > 0);
}

int main(void)
{
    printf("%d\n", tsub_ok(INT_MAX, 100));  // OK
    printf("%d\n", tsub_ok(INT_MIN, -100)); // OK
    printf("%d\n", tsub_ok(INT_MAX, -100)); // positive overflow
    printf("%d\n", tsub_ok(INT_MIN, 100));  // negative overflow
    printf("%d\n", tsub_ok(0, INT_MIN));    // negative overflow

    return 0;
}
