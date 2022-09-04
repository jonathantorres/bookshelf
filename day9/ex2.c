#include <stdio.h>

int cost;
int *p_cost;

int main(int argc, char const *argv[])
{
    // initialize pointer
    p_cost = &cost;

    // direct access
    cost = 100;

    // indirect access
    *p_cost = 101;

    printf("%d\n", p_cost);
    printf("%d\n", *p_cost);

    return 0;
}
