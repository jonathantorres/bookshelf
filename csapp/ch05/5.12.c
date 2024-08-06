#include <stdio.h>

void psum1(float a[], float p[], long n)
{
    long i;
    float last, val;

    last = p[0] = a[0];

    for (i = 1; i < n; i++) {
        val  = last + a[i];
        p[i] = val;
        last = val;
    }
}

int main(void)
{
    float a[]   = {3.1, 5.8, 9.99, 8.88, 4.09, 1.832};
    float b[10] = {0};
    float *p    = b;

    psum1(a, b, 6);

    while (1) {
        if (*p == 0) {
            break;
        }

        printf("%f, ", *p++);
    }

    printf("\n");

    return 0;
}
