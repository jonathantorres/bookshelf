#include <limits.h>
#include <stdio.h>

// Addition that saturates to TMin or TMax
int saturating_add(int x, int y)
{
    int sum      = x + y;
    int sig_mask = INT_MIN;
    int pos_over = !(x & sig_mask) && !(y & sig_mask) && (sum & sig_mask);
    int neg_over = (x & sig_mask) && (y & sig_mask) && !(sum & sig_mask);

    (pos_over && (sum = INT_MAX) || neg_over && (sum = INT_MIN));

    return sum;
}

int main(void)
{
    printf("%d\n", saturating_add(100, 100));                 // OK
    printf("%d\n", saturating_add(-2300, -5038));             // OK
    printf("%d\n", saturating_add(2000000000, 1000000000));   // Positive Overflow
    printf("%d\n", saturating_add(-2000000000, -2000000000)); // Negative Overflow

    return 0;
}
