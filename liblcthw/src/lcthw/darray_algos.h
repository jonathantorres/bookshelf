#ifndef darray_algos_h
#define darray_algos_h

#include "lcthw/darray.h"

int DArray_qsort(DArray *array, DArray_compare cmp);
int DArray_custom_qsort(DArray *array, DArray_compare cmp);
int DArray_heapsort(DArray *array, DArray_compare cmp);
int DArray_custom_heapsort(DArray *array, DArray_compare cmp);
int DArray_mergesort(DArray *array, DArray_compare cmp);
int DArray_custom_mergesort(DArray *array, DArray_compare cmp);
void *DArray_find(DArray *array, void *el_to_find, DArray_compare cmp, DArray_compare cmp2);

#endif
