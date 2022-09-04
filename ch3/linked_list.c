#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

linked_list_node *create_list_node(void *value)
{
    linked_list_node *node = malloc(sizeof(linked_list_node));

    if (!node) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = value;

    return node;
}

void destroy_list_node(linked_list_node *node)
{
    if (!node) {
        fputs("A valid node must be provided.", stderr);
        return;
    }

    node->prev = NULL;
    node->next = NULL;
    node->value = NULL;

    free(node);
}

// create a new list
linked_list *linked_list_new()
{
    linked_list *new_list = malloc(sizeof(linked_list));

    if (!new_list) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    new_list->first = NULL;

    return new_list;
}

// remove all the values in the list
void linked_list_clear(linked_list *list)
{
    if (list->first != NULL) {
        linked_list_node *current_node = list->first;

        while (current_node->next != NULL) {
            current_node = current_node->next;

            if (current_node->prev) {
                destroy_list_node(current_node->prev);
            }
        }

        if (current_node) {
            destroy_list_node(current_node);
        }

        list->first = NULL;
    }
}

// destroy the list
void linked_list_destroy(linked_list *list)
{
    if (!list) {
        fputs("Must provide a linked_list.", stderr);
        return;
    }

    linked_list_clear(list);
    free(list);
}

// get the length of the list
int linked_list_length(linked_list *list)
{
    if (!list) {
        fputs("Must provide a linked_list.", stderr);
        return -1;
    }

    int length = 0;

    if (list->first != NULL) {
        linked_list_node *current_node = list->first;
        length++;

        while (current_node->next != NULL) {
            current_node = current_node->next;
            length++;
        }
    }

    return length;
}

// insert at the end
void linked_list_push(linked_list *list, void *value)
{
    if (!list) {
        fputs("Must provide a linked_list.", stderr);
        return;
    }

    linked_list_node *new_node = create_list_node(value);

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        return;
    }

    linked_list_node *current_node = list->first;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    new_node->prev = current_node;
    current_node->next = new_node;
}

// insert at the beginning
void linked_list_shift(linked_list *list, void *value)
{
    if (!list) {
        fputs("Must provide a linked_list.", stderr);
        return;
    }

    linked_list_node *new_node = create_list_node(value);

    // list is empty, this is the first element
    if (list->first == NULL) {
        list->first = new_node;
        return;
    }

    list->first->prev = new_node;
    new_node->next = list->first;
    list->first = new_node;
}

// remove the first node and return it
void *linked_list_unshift(linked_list *list)
{
    if (!list) {
        fputs("Must provide a linked_list.", stderr);
        return NULL;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    // list has just 1 node
    if (list->first->next == NULL) {
        void *value = list->first->value;
        destroy_list_node(list->first);

        return value;
    }

    linked_list_node *new_first = list->first->next;
    void *value = list->first->value;

    destroy_list_node(list->first);
    new_first->prev = NULL;
    list->first = new_first;

    return value;
}

// remove the last node and return it
void *linked_list_pop(linked_list *list)
{
    if (!list) {
        fputs("Must provide a linked_list.", stderr);
        return NULL;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return NULL;
    }

    // list has just 1 node
    if (list->first->next == NULL) {
        void *value = list->first->value;
        destroy_list_node(list->first);
        list->first = NULL;

        return value;
    }

    linked_list_node *current_node = list->first;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    void *value = current_node->value;
    current_node->prev->next = NULL;
    destroy_list_node(current_node);

    return value;
}

// remove node whose value is {value}
void linked_list_remove(linked_list *list, void *value, linked_list_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid linked_list.", stderr);
        return;
    }

    // list is empty, return nothing
    if (list->first == NULL) {
        return;
    }

    // list has just 1 node
    if (list->first->next == NULL) {
        void *node_value = list->first->value;

        if (cmp(node_value, value) == 0) {
            linked_list_pop(list);
        }

        return;
    }

    linked_list_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        linked_list_node *next_node = current_node->next;
        next_node->prev = NULL;
        list->first = next_node;
        destroy_list_node(current_node);
        return;
    }

    while (current_node->next != NULL) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            // remove the node
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;
            destroy_list_node(current_node);
            break;
        }
    }
}

// check to see if value {value} exists in the list
bool linked_list_exists(linked_list *list, void *value, linked_list_cmp cmp)
{
    if (!list) {
        fputs("Must provide a valid linked_list.", stderr);
        return -1;
    }

    // list is empty, not found
    if (list->first == NULL) {
        return false;
    }

    linked_list_node *current_node = list->first;

    // check the first one
    if (cmp(current_node->value, value) == 0) {
        return true;
    }

    bool found = false;

    // check the rest
    while (current_node->next != NULL) {
        current_node = current_node->next;

        if (cmp(current_node->value, value) == 0) {
            found = true;
            break;
        }
    }

    return found;
}
