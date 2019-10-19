// 1-28. Write a function to perform integer division without using either the / or * operators. Find a fast way to do it.

#include <stdio.h>

int division(int dividend, int divisor)
{
    if (dividend == 0 || divisor == 0) {
        return 0;
    }

    int div = 0;
    int add = 0;
    while (add < dividend) {
        div++;
        add += divisor;
    }
    return div;
}

int main(void)
{
    printf("%d\n", division(2, 2));
    printf("%d\n", division(10, 5));
    printf("%d\n", division(250, 25));
    return 0;
}
