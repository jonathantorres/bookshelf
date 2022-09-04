#include <stdio.h>
#include <string.h>

int isupper1(int c);
int isupper2(int c);

int main(void)
{
    printf("%d\n", isupper1('G'));
    printf("%d\n", isupper1('t'));
    printf("%d\n", isupper2('K'));
    printf("%d\n", isupper2('m'));
    return 0;
}

int isupper1(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int isupper2(int c)
{
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}
