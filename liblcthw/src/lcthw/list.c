#include "lcthw/list.h"
#include "lcthw/dbg.h"

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    check(list != NULL, "The list cannot be NULL.");

    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);

error:
    return;
}

void List_clear(List *list)
{
    check(list != NULL, "The list cannot be NULL.");

    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }

error:
    return;
}

void List_clear_destroy(List *list)
{
    check(list != NULL, "The list cannot be NULL.");

    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);

        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);

error:
    return;
}

void List_push(List *list, void *value)
{
    check(list != NULL, "The list cannot be NULL.");

    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    check(list != NULL, "The list cannot be NULL.");

    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;

error:
    return NULL;
}

void List_unshift(List *list, void *value)
{
    check(list != NULL, "The list cannot be NULL.");

    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    check(list != NULL, "The list cannot be NULL.");

    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;

error:
    return NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "Node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;

        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

List *List_copy(List *list)
{
    check(list != NULL, "The list cannot be NULL.");

    List *new_list = List_create();

    LIST_FOREACH(list, first, next, cur) {
        List_push(new_list, cur->value);
    }

    return new_list;

error:
    return NULL;
}

List *List_join(List *list1, List *list2)
{
    check(list1 != NULL, "The first list cannot be NULL.");
    check(list2 != NULL, "The second list cannot be NULL.");

    List *new_list = List_copy(list1);

    LIST_FOREACH(list2, first, next, cur) {
        List_push(new_list, cur->value);
    }

    return new_list;

error:
    return NULL;
}

List **List_split(List *list)
{
    check(list != NULL, "The list cannot be NULL.");
    check(List_count(list) > 1, "The list must have at least 2 items.");

    List **splitted_list = calloc(2, sizeof(List));
    check_mem(splitted_list);

    int first_half = List_count(list) / 2;
    int second_half = List_count(list);
    int list_count = 0;
    List *first_list = List_create();
    List *second_list = List_create();

    LIST_FOREACH(list, first, next, cur) {
        if (list_count < first_half) {
            List_push(first_list, cur->value);
        } else if (list_count < second_half) {
            List_push(second_list, cur->value);
        }

        list_count++;
    }

    // TODO: I'm sure this can be done better, maybe use a pointer
    splitted_list[0] = first_list;
    splitted_list[1] = second_list;

    return splitted_list;

error:
    return NULL;
}

void List_print(List *list, char type)
{
    printf("{");
    LIST_FOREACH(list, first, next, cur) {
        switch(type) {
            case 'i':
                printf("%d,", *((int*)cur->value));
                break;
            case 's':
                printf("%s,", (char*)cur->value);
                break;
            case 'c':
                printf("%c,", *(char*)cur->value);
                break;
            default:
                printf("%p,", cur->value);
        }
    }
    printf("}\n");
}
