#include "priority_queue.h"

priority_queue *priority_queue_create(unsigned int capacity, size_t item_size, priority_queue_cmp cmp)
{
    priority_queue *p_queue = malloc(sizeof(priority_queue));
    if (!p_queue) {
        return NULL;
    }

    p_queue->queue = array_create(capacity, item_size);
    p_queue->cmp = cmp;
    if (!p_queue->queue) {
        return NULL;
    }

    return p_queue;
}

void priority_queue_destroy(priority_queue *p_queue)
{
    if (!p_queue) {
        return;
    }
    if (!p_queue->queue) {
        return;
    }
    array_destroy(p_queue->queue);
    free(p_queue);
}

int _p_queue_get_parent(int i)
{
    if (i == 0) {
        return -1;
    }

    return (int) (i-1)/2;
}

int _p_queue_left_child(int i)
{
    return (2*i) + 1;
}

void _p_queue_bubble_up(priority_queue *p_queue, int i)
{
    if (_p_queue_get_parent(i) == -1) {
        return;
    }

    int parent = _p_queue_get_parent(i);
    void *item1 = array_get(p_queue->queue, (unsigned int)parent);
    void *item2 = array_get(p_queue->queue, (unsigned int)i);

    if (p_queue->cmp(item1, item2) >= 0) {
        array_set(p_queue->queue, item1, i);
        array_set(p_queue->queue, item2, parent);
        _p_queue_bubble_up(p_queue, parent);
    }
}

void _p_queue_bubble_down(priority_queue *p_queue, int i)
{
    int child = _p_queue_left_child(i);
    int min_index = i;
    void *item1;
    void *item2;

    for (int j = 0; j <= 1; j++) {
        if (child+j <= (int)p_queue->queue->length-1) {
            item1 = array_get(p_queue->queue, (unsigned int)min_index);
            item2 = array_get(p_queue->queue, (unsigned int)child+j);
            if (p_queue->cmp(item1, item2) >= 0) {
                min_index = child+j;
            }
        }
    }

    if (min_index != i) {
        array_set(p_queue->queue, item1, i);
        array_set(p_queue->queue, item2, min_index);
        _p_queue_bubble_down(p_queue, min_index);
    }
}

void priority_queue_insert(priority_queue *p_queue, void *value)
{
    if (!p_queue) {
        return;
    }
    array_push(p_queue->queue, value);
    _p_queue_bubble_up(p_queue, p_queue->queue->length - 1);
}

void *priority_queue_extract_min(priority_queue *p_queue)
{
    if (!p_queue) {
        return NULL;
    }
    if (!p_queue->queue) {
        return NULL;
    }
    if (p_queue->queue->length == 0) {
        return NULL;
    }

    void *min = array_unshift(p_queue->queue);
    if (p_queue->queue->length > 0) {
        void *last = array_pop(p_queue->queue);
        array_shift(p_queue->queue, last);
        _p_queue_bubble_down(p_queue, 0);
    }

    return min;
}
