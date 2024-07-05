#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    puts("Ranges:");
    printf("signed char: from %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: from %d to %d\n", 0, UCHAR_MAX);
    printf("signed short: from %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: from %d to %d\n", 0, USHRT_MAX);
    printf("signed int: from %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: from %d to %u\n", 0U, UINT_MAX);
    printf("signed long: from %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: from %ld to %lu\n", 0UL, ULONG_MAX);
    printf("float: from %f to %f\n", FLT_MIN, FLT_MAX);
    printf("double: from %f to %f\n", DBL_MIN, DBL_MAX);

    return 0;
}
