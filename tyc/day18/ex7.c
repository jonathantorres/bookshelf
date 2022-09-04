#include <stdio.h>
#include <stdlib.h>

struct nums {
    void* smaller;
    void* larger;
};

struct nums find_larger_and_smaller(void *numbers, int length, char type);

int main(void)
{
    int int_arr[5] = { 56, 901, 22, 111, 8 };
    float float_arr[5] = { 77.0, 50.63, 88.9, -100.1, 78.4 };

    struct nums int_numbers = find_larger_and_smaller(int_arr, 5, 'i');
    struct nums float_numbers = find_larger_and_smaller(float_arr, 5, 'f');

    printf("Larger is %d and smallest is %d\n", *(int*)int_numbers.larger, *(int*)int_numbers.smaller);
    printf("Larger is %f and smallest is %f\n", *(float*)float_numbers.larger, *(float*)float_numbers.smaller);
    return 0;
}

struct nums find_larger_and_smaller(void *numbers, int length, char type)
{
    struct nums results;

    switch (type) {
        case 'i': {
            int *numbers_p = (int*)numbers;
            int *largest_p = numbers_p;
            int *smallest_p = numbers_p;

            for (int i = 0; i < length; i++) {
                if (*numbers_p > *largest_p) {
                    largest_p = numbers_p;
                }

                if (*numbers_p < *smallest_p) {
                    smallest_p = numbers_p;
                }
                numbers_p++;
            }
            results.smaller = smallest_p;
            results.larger = largest_p;
            break;
        }
        case 'f': {
            float *numbers_p = (float*)numbers;
            float *largest_p = numbers_p;
            float *smallest_p = numbers_p;

            for (int i = 0; i < length; i++) {
                if (*numbers_p > *largest_p) {
                    largest_p = numbers_p;
                }

                if (*numbers_p < *smallest_p) {
                    smallest_p = numbers_p;
                }
                numbers_p++;
            }
            results.smaller = smallest_p;
            results.larger = largest_p;
            break;
        }
        default: {
            puts("Type is not supported.");
            exit(1);
        }
    }

    return results;
}
