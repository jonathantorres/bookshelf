#ifndef _priority_queue_h
#define _priority_queue_h

#include "array.h"
#include <stdlib.h>
#include <stdio.h>

typedef int (*priority_queue_cmp)(void *a, void *b);

typedef struct priority_queue {
    array *queue;
    priority_queue_cmp cmp;
} priority_queue;

priority_queue *priority_queue_create(unsigned int capacity, size_t item_size, priority_queue_cmp cmp);
void priority_queue_destroy(priority_queue *p_queue);
void priority_queue_insert(priority_queue *p_queue, void *value);
void *priority_queue_extract_min(priority_queue *p_queue);

#endif
