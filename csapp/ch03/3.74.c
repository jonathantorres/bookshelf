#include <stdio.h>

typedef enum { NEG, ZERO, POS, OTHER } range_t;

range_t find_range(float x)
{
    __asm__("vxorps %xmm1, %xmm1, %xmm1\n\t"
            "movq $1, %rax\n\t"
            "movq $2, %r8\n\t"
            "movq $0, %r9\n\t"
            "movq $3, %r10\n\t"
            "vucomiss %xmm1, %xmm0\n\t"
            "cmovaq %r8, %rax\n\t"
            "cmovbq %r9, %rax\n\t"
            "cmovpq %r10, %rax\n\t");
}

int main(void)
{
    float x = 3432.2342;

    printf("%d\n", find_range(x));

    return 0;
}
