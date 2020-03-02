#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    unsigned long num;
    int *ptr;

    printf("Enter the number of type int to allocate: ");
    scanf("%ld", &num);

    ptr = (int*) calloc(num, sizeof(long long));

    if (ptr != NULL) {
        puts("Memory allocation was successfull.");
    } else {
        puts("Memory allocation failed.");
    }

    return 0;
}
