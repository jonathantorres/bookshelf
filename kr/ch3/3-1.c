#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{
    int v[] = {1, 2, 3, 4, 5, 6};

    printf("%d\n", binsearch(2, v, 6));
    printf("%d\n", binsearch(6, v, 6));
    printf("%d\n", binsearch(10, v, 6));

    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low  = 0;
    high = n - 1;
    mid  = (low + high) / 2;

    while (low <= high && v[mid] != x) {
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }

        mid = (low + high) / 2;
    }

    if (v[mid] == x) {
        return mid;
    }

    return -1;
}
