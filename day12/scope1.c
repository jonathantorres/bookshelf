#include <stdio.h>

int x = 999;

void print_value(void);

int main(int argc, char const *argv[])
{
    printf("%d\n", x);
    print_value();

    return 0;
}

void print_value(void)
{
    printf("%d\n", x);
}
