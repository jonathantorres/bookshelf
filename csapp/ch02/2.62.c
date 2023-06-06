#include <stdio.h>

int int_shifts_are_arithmetic()
{
    return (~0 >> 1) == ~0;
}

int main(void)
{
    printf("%d\n", int_shifts_are_arithmetic());

    return 0;
}
