#ifndef _linked_list_h
#define _linked_list_h

#include <stdbool.h>

typedef struct linked_list_node {
    void *value;
    struct linked_list_node *next;
    struct linked_list_node *prev;
} linked_list_node;

typedef struct linked_list {
    linked_list_node *first;
} linked_list;

typedef int(*linked_list_cmp)(void *a, void *b);

// create a new list
linked_list *linked_list_new();

// remove all the values in the list
void linked_list_clear(linked_list *list);

// destroy the list
void linked_list_destroy(linked_list *list);

// get the length of the list
int linked_list_length(linked_list *list);

// insert at the end
void linked_list_push(linked_list *list, void *value);

// insert at the beginning
void linked_list_shift(linked_list *list, void *value);

// remove the first node and return it
void *linked_list_unshift(linked_list *list);

// remove the last node and return it
void *linked_list_pop(linked_list *list);

// remove node whose value is {value}
void linked_list_remove(linked_list *list, void *value, linked_list_cmp cmp);

// check to see if value {value} exists in the list
bool linked_list_exists(linked_list *list, void *value, linked_list_cmp cmp);

// Macro usage:
// LINKED_LIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define LINKED_LIST_FOREACH(list) \
    for (linked_list_node *cur = (list)->first; cur != NULL; cur = cur->next)

#endif
