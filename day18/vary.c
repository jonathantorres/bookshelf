#include <stdio.h>
#include <stdarg.h>

float average(int num, ...);

int main(void)
{
    float x;

    x = average(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    printf("The first average is %f\n", x);
    x = average(5, 121, 206, 76, 31, 5);
    printf("The second average is %f\n", x);
    return 0;
}

float average(int num, ...)
{
    va_list arg_ptr;
    int count, total = 0;

    va_start(arg_ptr, num);

    for (count = 0; count < num; count++) {
        total += va_arg(arg_ptr, int);
    }

    va_end(arg_ptr);

    return ((float) total / num);
}
