#include <stdio.h>

int global_var = 100;

int main(int argc, char const *argv[])
{
    int global_var = 150;

    printf("%d\n", global_var);
    return 0;
}
