#include <stdio.h>

int var = 1;
int *ptr;

int main(int argc, char const *argv[])
{
    ptr = &var;

    printf("\nDirect access, var = %d", var);
    printf("\nIndirect access, var = %d", *ptr);
    printf("\nThe address of var = %d", &var);
    printf("\nThe address of var = %d", ptr);

    return 0;
}
