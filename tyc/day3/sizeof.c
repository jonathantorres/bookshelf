#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("\nA char is %ld bytes", sizeof(char));
    printf("\nAn int is %ld bytes", sizeof(int));
    printf("\nA short is %ld bytes", sizeof(short));
    printf("\nA long is %ld bytes", sizeof(long));
    printf("\nA long long is %ld bytes\n", sizeof(long long));
    printf("\nAn unsigned char is %ld bytes", sizeof(unsigned char));
    printf("\nAn unsigned int is %ld bytes", sizeof(unsigned int));
    printf("\nAn unsigned short is %ld bytes", sizeof(unsigned short));
    printf("\nAn unsigned long is %ld bytes", sizeof(unsigned long));
    printf("\nAn unsigned long long is %ld bytes\n", sizeof(unsigned long long));
    printf("\nA float is %ld bytes", sizeof(float));
    printf("\nA double is %ld bytes", sizeof(double));
    printf("\nA long double is %ld bytes\n", sizeof(long double));
    printf("Size: %ld\n", sizeof(500));
    return 0;
}
