#include "heap_sort.h"

priority_queue *make_heap(array *_array, cmp_f cmp)
{
    priority_queue *p_queue = priority_queue_create(_array->capacity, _array->item_size, cmp);
    if (!p_queue) {
        return NULL;
    }
    for (unsigned int i = 0; i < _array->length; i++) {
        priority_queue_insert(p_queue, array_get(_array, i));
    }
    return p_queue;
}

void heap_sort(array *_array, cmp_f cmp)
{
    if (!_array) {
        fputs("[heap_sort] Must provide an array.", stderr);
        return;
    }
    priority_queue *p_queue = make_heap(_array, cmp);
    for (unsigned int i = 0; i < p_queue->queue->length; i++) {
        array_set(_array, priority_queue_extract_min(p_queue), i);
    }
}
