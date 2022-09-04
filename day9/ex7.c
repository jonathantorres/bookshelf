#include <stdio.h>

int sumarrays(int *array1, int array1_length, int *array2, int array2_length);

#define LENGTH 10

int numbers1[] = {
    100,21,34,123,800,
    1098,211,14,3,20
};
int numbers2[] = {
    10,1,3,12,0,
    98,231,141,334,18
};

int main(int argc, char const *argv[])
{
    printf("%d\n", sumarrays(numbers1, LENGTH, numbers2, LENGTH));
    return 0;
}

int sumarrays(int *array1, int array1_length, int *array2, int array2_length)
{
    int total = 0;

    for (int i = 0; i < array1_length; i++) {
        total += *array1++;
        for (int i = 0; i < array2_length; i++) {
            total += *array2++;
        }
    }

    return total;
}
