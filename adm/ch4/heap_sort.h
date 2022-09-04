#ifndef _heap_sort_h
#define _heap_sort_h

#include "array.h"
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef int(*cmp_f)(void *a, void *b);
void heap_sort(array *_array, cmp_f cmp);

#endif
