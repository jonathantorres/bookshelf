#include <stdio.h>

// A: The problem with this code is that it always returns a positive number. The mask zeroes out
// the most significant bits

// B: Changes below

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
    return (char)(word >> (bytenum << 3));
}

int main(void)
{
    packed_t w = 0xFF187FBB;

    printf("%d\n", xbyte(w, 0));
    printf("%d\n", xbyte(w, 1));
    printf("%d\n", xbyte(w, 2));
    printf("%d\n", xbyte(w, 3));

    return 0;
}
