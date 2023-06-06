#include <stdio.h>

// A: It fails to comply with the requirement that the shift amount
//    must be less than the word size

// B: machine in which an int is at least 32 bits
int int_size_is_32()
{
    int set_msb    = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

// C: machine in which an int is at least 16 bits
int int_size_is_32_()
{
    int set_msb    = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main(void)
{
    printf("%d\n", int_size_is_32());
    printf("%d\n", int_size_is_32_());

    return 0;
}
