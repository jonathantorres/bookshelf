#include <stdio.h>

int main(int argc, char const *argv[])
{
    int my_age = 32;
    int *p_my_age = &my_age;

    printf("my_age value is: %d\n", my_age);
    printf("my_age address is: %d\n", *p_my_age);
    return 0;
}
