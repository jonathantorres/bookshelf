#include <stdio.h>
#include <string.h>

int my_func(char *str);
int numbers(int *a, int *b, int *c);

int main(int argc, char const *argv[])
{
    char msg[] = "Hello, World";
    printf("The length of the string is %d\n", my_func(msg));

    int a = 1, b = 2, c = 3;
    numbers(&a, &b, &c);
    return 0;
}

int my_func(char *str)
{
    return strlen(str);
}
