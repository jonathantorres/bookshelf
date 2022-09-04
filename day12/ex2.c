#include <stdio.h>

void print_value(void);

int main(int argc, char const *argv[])
{
    int x = 999;

    printf("%d\n", x);
    print_value();

    return 0;
}

void print_value(void)
{
    int x = 999;
    printf("%d\n", x);
}
