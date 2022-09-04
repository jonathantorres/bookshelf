#include <stdio.h>

int intarray[100];
float floatarray[100];
double doublearray[100];

int main(int argc, char const *argv[])
{
    printf("Size of int = %lu bytes", sizeof(int));
    printf("\nSize of short = %lu bytes", sizeof(short));
    printf("\nSize of long = %lu bytes", sizeof(long));
    printf("\nSize of long long = %lu bytes", sizeof(long long));
    printf("\nSize of float = %lu bytes", sizeof(float));
    printf("\nSize of double = %lu bytes", sizeof(double));
    printf("\nSize of intarray = %lu bytes", sizeof(intarray));
    printf("\nSize of floatarray = %lu bytes", sizeof(floatarray));
    printf("\nSize of doublearray = %lu bytes\n", sizeof(doublearray));

    return 0;
}
