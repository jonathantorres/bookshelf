#include <stdio.h>

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main(void)
{
    int nums[10] = { 12, 14, 77, 99, 101, 189, 293, 890, 991, 1065 };
    printf("%d\n", binsearch2(77, nums, 10)); // 2
    printf("%d\n", binsearch2(66, nums, 10)); // -1
    return 0;
}

int binsearch2(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    while ((low <= high) && (v[mid] != x)) {
        mid = (low+high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ((v[mid] == x) ? mid : -1);
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
