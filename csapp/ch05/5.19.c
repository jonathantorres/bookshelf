#include <stdio.h>

void psum_fast(float a[], float p[], long n)
{
    long i;
    float val, last_val;
    float tmp0, tmp1, tmp2, tmp3;

    last_val = p[0] = a[0];

    for (i = 1; i < n - 4; i++) {
        tmp0 = last_val + a[i];
        tmp1 = tmp0 + a[i + 1];
        tmp2 = tmp1 + a[i + 2];
        tmp3 = tmp2 + a[i + 3];

        p[i]     = tmp0;
        p[i + 1] = tmp1;
        p[i + 2] = tmp2;
        p[i + 3] = tmp3;

        last_val = last_val + (a[i] + a[i + 1] + a[i + 2] + a[i + 3]);
    }

    for (; i < n; i++) {
        last_val += a[i];
        p[i] = last_val;
    }
}

int main(void)
{
    long n    = 7;
    float a[] = {2, 3, 4, 5, 7, 8, 10};
    float b[] = {7, 9, 2, 8, 0, 9, 22};

    psum_fast(a, b, n);

    return 0;
}
