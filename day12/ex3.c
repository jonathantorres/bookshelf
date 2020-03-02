#include <stdio.h>

void print_it(int val);

int main(int argc, char const *argv[])
{
    int var = 250;
    print_it(var);
    return 0;
}

void print_it(int val)
{
    printf("%d\n", val);
}
