#include <stdio.h>

void addarrays(int *array1, int *array2, int length);

#define LENGTH 5

int nums1[] = { 1, 2, 3, 4, 5 };
int nums2[] = { 6, 7, 8, 9, 10 };
int final_nums[10];

int main(int argc, char const *argv[])
{
    addarrays(nums1, nums2, LENGTH);

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", final_nums[i]);
    }

    return 0;
}

void addarrays(int *array1, int *array2, int length)
{
    for (int i = 0; i < length; i++)
    {
        final_nums[i] = *array1++;
    }

    for (int i = 5; i < length*2; i++)
    {
        final_nums[i] = *array2++;
    }
}
