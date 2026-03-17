#include <stdio.h>
#include <stdlib.h>
#include "common_threads.h"

typedef struct __node_t {
    int key;
    pthread_mutex_t lock;
    struct __node_t *next;
} node_t;

typedef struct __list_t {
    node_t *head;
} list_t;

#define MAXITEMS 10000

void list_init(list_t *list)
{
    list->head = NULL;
}

int list_insert(list_t *list, int key)
{
    node_t *new = malloc(sizeof(node_t));
    if (!new) {
        return -1;
    }
    new->key = key;
    new->next = list->head;
    Mutex_init(&new->lock);
    list->head = new;
    return 0;
}

int list_lookup(list_t *list, int key)
{
    node_t *curr = list->head;
    while (curr) {
        Pthread_mutex_lock(&curr->lock);
        if (curr->key == key) {
            Pthread_mutex_unlock(&curr->lock);
            return 0;
        }
        Pthread_mutex_unlock(&curr->lock);
        curr = curr->next;
    }
    return -1;
}

int main(void)
{
    list_t *list = malloc(sizeof(list_t));
    if (!list) {
        return 1;
    }
    list_init(list);
    for (int i = 1; i <= MAXITEMS; i++) {
        list_insert(list, i);
    }
    printf("%d\n", list_lookup(list, 789));
    return 0;
}
