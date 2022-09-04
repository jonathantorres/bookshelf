/**
 * Write a program to reverse the direction of a given singly-linked list. In other words, after the reversal all pointers should now point backwards. Your algorithm should take linear time.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct list_node {
    void *value;
    struct list_node *next;
} list_node;

typedef struct list {
    list_node *first;
} list;

// Macro usage:
// SLLIST_FOREACH(list) {
    // your code here
    // you can use the variable "cur"
    // inside of it that references the current item of the list
// }
#define LIST_FOREACH(_list) \
    for (list_node *cur = (_list)->first; cur != NULL; cur = cur->next)

list_node *create_node(void *value);
void destroy_node(list_node *node);
list *list_new();
void list_clear(list *_list);
void list_destroy(list *_list);
void list_push(list *_list, void *value);
void list_reverse(list *_list);
int list_length(list *_list);

void list_reverse(list *_list)
{
    if (!_list) {
        return;
    }
    if (list_length(_list) == 0) {
        return;
    }
    list_node *cur_node = _list->first;
    list_node *prev_node = NULL;
    list_node *next_node = NULL;

    while (cur_node != NULL) {
        next_node = cur_node->next;
        cur_node->next = prev_node;
        prev_node = cur_node;
        cur_node = next_node;
    }
    _list->first = prev_node;
}

list_node *create_node(void *value)
{
    list_node *node = malloc(sizeof(list_node));

    if (!node) {
        return NULL;
    }

    node->next = NULL;
    node->value = value;

    return node;
}

void destroy_node(list_node *node)
{
    if (!node) {
        return;
    }

    node->next = NULL;
    node->value = NULL;

    free(node);
}

list *list_new()
{
    list *new_list = malloc(sizeof(list));

    if (!new_list) {
        return NULL;
    }

    new_list->first = NULL;

    return new_list;
}

void list_clear(list *_list)
{
    if (_list->first != NULL) {
        list_node *current_node = _list->first;
        list_node *prev_node = NULL;

        while (current_node->next != NULL) {
            prev_node = current_node;
            current_node = current_node->next;

            if (prev_node) {
                destroy_node(prev_node);
            }
        }

        if (current_node) {
            destroy_node(current_node);
        }

        _list->first = NULL;
    }
}

void list_destroy(list *_list)
{
    if (!_list) {
        return;
    }

    list_clear(_list);
    free(_list);
}

// get the length of the list
int list_length(list *_list)
{
    if (!_list) {
        return -1;
    }

    int length = 0;

    if (_list->first != NULL) {
        list_node *current_node = _list->first;
        length++;

        while (current_node->next != NULL) {
            current_node = current_node->next;
            length++;
        }
    }

    return length;
}

// insert at the end
void list_push(list *_list, void *value)
{
    if (!_list) {
        return;
    }

    list_node *new_node = create_node(value);

    // list is empty, this is the first element
    if (_list->first == NULL) {
        _list->first = new_node;
        return;
    }

    list_node *current_node = _list->first;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;
}

int main(void)
{
    list *names = list_new();
    list_push(names, strdup("Jonathan"));
    list_push(names, strdup("George"));
    list_push(names, strdup("Billy"));
    list_push(names, strdup("Marcus"));
    LIST_FOREACH(names) {
        printf("- %s\n", (char*)cur->value);
    }
    puts("");
    list_reverse(names);
    LIST_FOREACH(names) {
        printf("- %s\n", (char*)cur->value);
    }
    list_destroy(names);
    return 0;
}
