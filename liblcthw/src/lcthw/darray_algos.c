#include <stdlib.h>
#include "lcthw/darray_algos.h"

int DArray_qsort(DArray *array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void*), cmp);
    return 0;
}

int quicksort_partition(DArray *array, int low, int hi, DArray_compare cmp)
{
    void *pivot = DArray_get(array, hi);
    int i = low;

    for (int j = low; j <= hi - 1; j++) {
        if (cmp((char*)DArray_get(array, j), (char*)pivot) <= 0) {
            DArray_swap(array, i, j);
            i = i + 1;
        }
    }

    DArray_swap(array, i, hi);
    return i;
}

void custom_quicksort(DArray *array, int low, int hi, DArray_compare cmp)
{
    if (low < hi) {
        int p = quicksort_partition(array, low, hi, cmp);
        custom_quicksort(array, low, p - 1, cmp);
        custom_quicksort(array, p + 1, hi, cmp);
    }
}

int DArray_custom_qsort(DArray *array, DArray_compare cmp)
{
    custom_quicksort(array, 0, DArray_count(array) - 1, cmp);
    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    return heapsort(array->contents, DArray_count(array), sizeof(void*), cmp);
}

int DArray_custom_heapsort(DArray *array, DArray_compare cmp)
{
    // TODO!
    return 0;
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    return mergesort(array->contents, DArray_count(array), sizeof(void*), cmp);
}

DArray *DArray_custom_merge(DArray *left, DArray *right, DArray_compare cmp)
{
    DArray *result = DArray_create(left->element_size, 1);

    while (DArray_count(left) > 0 && DArray_count(right) > 0) {
        if (cmp((char*)DArray_first(left), (char*)DArray_first(right)) <= 0) {
            DArray_push(result, DArray_first(left));
            // TODO: implement DArray_unshift!
        } else {
            DArray_push(result, DArray_first(right));
            // TODO: implement DArray_unshift!
        }
    }

    while (DArray_count(left) > 0) {
        DArray_push(result, DArray_first(left));
        // TODO: implement DArray_unshift!
    }

    while (DArray_count(right) > 0) {
        DArray_push(result, DArray_first(right));
        // TODO: implement DArray_unshift!
    }

    return result;
}

int DArray_custom_mergesort(DArray *array, DArray_compare cmp)
{
    if (DArray_count(array) <= 1) {
        return 0;
    }

    DArray *left = DArray_create(array->element_size, DArray_count(array) / 2);
    DArray *right = DArray_create(array->element_size, DArray_count(array) / 2);

    for (int i = 0; i < DArray_count(array); i++) {
        void *elem = DArray_get(array, i);

        if (i < DArray_count(array) / 2) {
            DArray_set(left, i, elem);
        } else {
            DArray_set(right, i, elem);
        }
    }

    left = DArray_custom_mergesort(left, cmp);
    right = DArray_custom_mergesort(right, cmp);
    array = DArray_custom_merge(left, right, cmp);

    return 0;
}

void *DArray_find(DArray *array, void *el_to_find, DArray_compare cmp, DArray_compare cmp2)
{
    check(array != NULL, "The array cannot be NULL");
    DArray_qsort(array, cmp);

    int low = 0;
    int high = array->end - 1;

    while (low <= high) {
        int middle = low + (high - low) / 2;
        void *current = array->contents[middle];

        if (cmp2(el_to_find, current) < 0) {
            high = middle - 1;
        } else if (cmp2(el_to_find, current) > 0) {
            low = middle + 1;
        } else {
            return array->contents[middle];
        }
    }

error:
    return NULL;
}
