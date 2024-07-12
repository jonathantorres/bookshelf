#include <stdio.h>

int tadd_ok(int x, int y)
{
    int sum = x + y;
    return !(x > 0 && y > 0 && sum <= 0) && !(x < 0 && y < 0 && sum >= 0);
}

int main(void)
{
    printf("%d\n", tadd_ok(500, 234323));

    return 0;
}
