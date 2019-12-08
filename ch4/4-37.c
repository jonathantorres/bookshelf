/**
 * 4-37 - Implement versions of several different sorting algorithms, such as selection sort, insertion sort, heapsort, mergesort, and quicksort. Conduct experiments to assess the relative performance of these algorithms in a simple application that reads a large text file and reports exactly one instance of each word that appears within it. This application can be efficiently implemented by sorting all the words that occur in the text and then passing through the sorted sequence to identify one instance of each distinct word. Write a brief report with your conclusions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "bubble_sort.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

int cmp_int(void *a, void *b)
{
    if (*(int*)a > *(int*)b) {
        return 1;
    } else if (*(int*)a < *(int*)b) {
        return -1;
    } else {
        return 0;
    }
}

// utility method to print the contents of an array
// in this test we'll be using an array of numbers
void array_print(array *_array, char type)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("[");
    for (unsigned int i = 0; i < _array->length; i++) {
        void *val = NULL;
        switch (type) {
            case 'i':
                val = (int*)array_get(_array, i);
                printf("%d,", *(int*)val);
            break;

            case 's':
                val = array_get(_array, i);
                printf("%s,", (char*)val);
            break;
        }
    }
    printf("]\n");
}

// generate a random number between 1 and 50
int gen_random_number()
{
    int lower = 1;
    int upper = 50;
    return (rand() % (upper - lower + 1)) + lower;
}

void run_selection_sort()
{
    array *_array = array_create(15, sizeof(int*));

    for (unsigned int i = 0; i < 15; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = gen_random_number();
            array_push(_array, value);
        }
    }
    printf("selection sort:");
    array_print(_array, 'i');
    selection_sort(_array, cmp_int);
    printf("selection sort:");
    array_print(_array, 'i');
}

void run_insertion_sort()
{
    array *_array = array_create(15, sizeof(int*));

    for (unsigned int i = 0; i < 15; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = gen_random_number();
            array_push(_array, value);
        }
    }
    printf("insertion sort:");
    array_print(_array, 'i');
    insertion_sort(_array, cmp_int);
    printf("insertion sort:");
    array_print(_array, 'i');
}

void run_merge_sort()
{
    array *_array = array_create(25, sizeof(int*));

    for (unsigned int i = 0; i < 25; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = gen_random_number();
            array_push(_array, value);
        }
    }
    printf("merge sort:");
    array_print(_array, 'i');
    merge_sort(_array, cmp_int);
    printf("merge sort:");
    array_print(_array, 'i');
}

void run_quick_sort()
{
    array *_array = array_create(25, sizeof(int*));

    for (unsigned int i = 0; i < 25; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = gen_random_number();
            array_push(_array, value);
        }
    }
    printf("quick sort:");
    array_print(_array, 'i');
    quick_sort(_array, cmp_int);
    printf("quick sort:");
    array_print(_array, 'i');
}

void run_bubble_sort()
{
    array *_array = array_create(10, sizeof(int*));

    for (unsigned int i = 0; i < 10; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = gen_random_number();
            array_push(_array, value);
        }
    }
    printf("bubble sort:");
    array_print(_array, 'i');
    bubble_sort(_array, cmp_int);
    printf("bubble sort:");
    array_print(_array, 'i');
}

int main(void)
{
    run_bubble_sort();
    run_insertion_sort();
    run_selection_sort();
    run_merge_sort();
    run_quick_sort();
    return 0;
}
