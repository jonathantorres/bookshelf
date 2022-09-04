#ifndef lcthw_queue_h
#define lcthw_queue_h

#include "list.h"

typedef struct Queue {
    List *list;
} Queue;

Queue *Queue_create();
void Queue_destroy(Queue *queue);
void Queue_send(Queue *queue, void *value);
void *Queue_peek(Queue *queue);
void *Queue_recv(Queue *queue);
int Queue_count(Queue *queue);

#define QUEUE_FOREACH(queue, cur) \
    LIST_FOREACH(queue->list, first, next, cur)

#endif

