#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    puts("Max ranges:");
    printf("char:\t\t %d\n", CHAR_MAX);
    printf("short:\t\t %d\n", SHRT_MAX);
    printf("int:\t\t %d\n", INT_MAX);
    printf("unsigned int:\t %d\n", UINT_MAX);
    printf("long:\t\t %ld\n", LONG_MAX);
    printf("float:\t\t %f\n", FLT_MAX);
    printf("double:\t\t %f\n", DBL_MAX);
    printf("long double:\t %Lf\n", LDBL_MAX);

    puts("");
    puts("Sizes:");
    printf("char:\t\t %lu\n", sizeof(char));
    printf("short:\t\t %lu\n", sizeof(short));
    printf("int:\t\t %lu\n", sizeof(int));
    printf("unsigned int:\t %lu\n", sizeof(unsigned int));
    printf("long:\t\t %lu\n", sizeof(long));
    printf("float:\t\t %lu\n", sizeof(float));
    printf("double:\t\t %lu\n", sizeof(double));
    printf("long double:\t %lu\n", sizeof(long double));
    return 0;
}
