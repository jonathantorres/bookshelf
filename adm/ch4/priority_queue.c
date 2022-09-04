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

int _p_queue_right_child(int i)
{
    return (2*i) + 2;
}

void _p_queue_bubble_up(priority_queue *p_queue, int item_index)
{
    if (_p_queue_get_parent(item_index) == -1) {
        return;
    }

    int parent_index = _p_queue_get_parent(item_index);
    void *parent_item = array_get(p_queue->queue, (unsigned int)parent_index);
    void *child_item = array_get(p_queue->queue, (unsigned int)item_index);

    if (p_queue->cmp(parent_item, child_item) >= 0) {
        array_set(p_queue->queue, parent_item, item_index);
        array_set(p_queue->queue, child_item, parent_index);
        _p_queue_bubble_up(p_queue, parent_index);
    }
}

void _p_queue_bubble_down(priority_queue *p_queue, int current_i)
{
    int left_i = _p_queue_left_child(current_i);
    int right_i = _p_queue_right_child(current_i);
    int min_i = current_i;

    void *left_item = array_get(p_queue->queue, (unsigned int)left_i);
    void *current_item = array_get(p_queue->queue, (unsigned int)current_i);

    if (left_i < (int)p_queue->queue->length-1 && p_queue->cmp(left_item, current_item) <= 0) {
        min_i = left_i;
    }

    void *right_item = array_get(p_queue->queue, (unsigned int)right_i);
    void *min_item = array_get(p_queue->queue, (unsigned int)min_i);

    if (right_i < (int)p_queue->queue->length-1 && p_queue->cmp(right_item, min_item) <= 0) {
        min_i = right_i;
    }

    if (min_i != current_i) {
        array_set(p_queue->queue, min_item, current_i);
        array_set(p_queue->queue, current_item, min_i);
        _p_queue_bubble_down(p_queue, min_i);
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
