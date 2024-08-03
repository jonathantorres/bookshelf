#include <limits.h>
#include <stdio.h>

/* A: It fails to comply with the requirement that the shift amount */
/*    must be less than the word size */

/* B: Changes on the code */
int int_size_is_32()
{
    int set_msb    = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

/* C: changes to support 16 bit machines */
int int_size_is_32_16_min()
{
    int set_msb    = INT_MIN;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main(void)
{
    printf("%d\n", int_size_is_32());
    printf("%d\n", int_size_is_32_16_min());

    return 0;
}
