#include <stdio.h>

typedef enum { NEG, ZERO, POS, OTHER } range_t;

range_t find_range(float x)
{
    __asm__("vxorps %xmm1, %xmm1, %xmm1\n\t"
            "vucomiss %xmm1, %xmm0\n\t"
            "jp .P\n\t"
            "ja .A\n\t"
            "jb .B\n\t"
            "je .E\n\t"
            ".A:\n\t"
            "movl $2, %eax\n\t"
            "jmp .Done\n\t"
            ".B:\n\t"
            "movl $0, %eax\n\t"
            "jmp .Done\n\t"
            ".E:\n\t"
            "movl $1, %eax\n\t"
            "jmp .Done\n\t"
            ".P:\n\t"
            "movl $3, %eax\n\t"
            ".Done:\n\t");
}

int main(void)
{
    float x = 55.2342;

    printf("%d\n", find_range(x));

    return 0;
}
