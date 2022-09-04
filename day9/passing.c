#include <stdio.h>

#define MAX 10

int array[MAX], count;
int largest(int num_array[], int length);

int main(int argc, char const *argv[])
{
    for (count = 0; count < MAX; count++) {
        printf("Enter an integer value: ");
        scanf("%d", &array[count]);
    }

    printf("\n\nLargest value = %d\n", largest(array, MAX));

    return 0;
}

int largest(int num_array[], int length)
{
    int count;
    int biggest = 0;

    for (count = 0; count < length; count++) {
        if (num_array[count] > biggest) {
            biggest = num_array[count];
        }
    }

    return biggest;
}
