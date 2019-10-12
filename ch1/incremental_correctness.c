// Chapter 1 - Page 16 - Stop and Think: Incremental Correctness
#include <stdio.h>
#include <math.h>

int increment(int y);

int increment(int y)
{
    if (y == 0) {
        return 1;
    }

    if (y % 2 == 1) {
        return 2 * increment((int)floor(y / 2));
    } else {
        return y + 1;
    }
}

int main(void)
{
    printf("%d\n", increment(0));
    printf("%d\n", increment(1));
    printf("%d\n", increment(2));
    return 0;
}
