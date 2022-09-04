#include <stdio.h>

int a, b;

int main(int argc, char const *argv[])
{
    a = b = 5;

    printf("\nPost    Pre");
    printf("\n%d      %d", a--, --b);
    printf("\n%d      %d", a--, --b);
    printf("\n%d      %d", a--, --b);
    printf("\n%d      %d", a--, --b);
    printf("\n%d      %d\n", a--, --b);

    return 0;
}
