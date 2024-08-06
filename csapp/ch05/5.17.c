#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *memset_fast(void *s, int c, size_t n)
{
    size_t k             = sizeof(unsigned long);
    size_t cnt           = 0;
    unsigned char *schar = s;

    while ((cnt < n) && (size_t)schar % k != 0) {
        *schar++ = (unsigned char)c;
        cnt++;
    }

    unsigned long new_c = c;

    for (size_t shift = 1; shift < k; shift *= 2) {
        new_c = (new_c << shift * 8) + new_c;
    }

    unsigned long *long_k = (unsigned long *)schar;
    size_t limit          = n - cnt - k;

    for (; cnt < limit; cnt += k) {
        *long_k++ = new_c;
    }

    schar = (unsigned char *)long_k;

    for (; cnt < n; cnt++) {
        *schar++ = (unsigned char)c;
    }

    return s;
}

int main(void)
{
    size_t n = 2048;
    void *s1 = malloc(n * sizeof(long));

    if (!s1) {
        printf("Out of memory!\n");
        return 1;
    }

    void *s2 = malloc(n * sizeof(long));

    if (!s2) {
        printf("Out of memory!\n");
        return 1;
    }

    memset_fast(s1, 0xFF, n);
    memset(s2, 0xFF, n);

    if (memcmp(s1, s2, n) == 0) {
        printf("test passed.\n");
    } else {
        printf("ERROR! test failed!\n");
    }

    free(s1);
    free(s2);

    return 0;
}
