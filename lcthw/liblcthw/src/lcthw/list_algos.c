#include "lcthw/list_algos.h"

void ListNode_swap(ListNode *node1, ListNode *node2)
{
    void *tmp1 = node1->value;
    node1->value = node2->value;
    node2->value = tmp1;
}

int List_bubble_sort(List *list, List_compare cmp)
{
    int swapped;

    do {
        swapped = 0;
        LIST_FOREACH(list, first, next, cur) {
            if (cur->next) {
                if (cmp((char*)cur->value, (char*)cur->next->value) > 0) {
                    ListNode_swap(cur, cur->next);
                    swapped = 1;
                }
            }
        }
    } while (swapped == 1);

    return 0;
}

List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();

    while (left->count != 0 && right->count != 0) {
        if (cmp((char*)left->first->value, (char*)right->first->value) <= 0) {
            List_push(result, left->first->value);
            List_shift(left);
        } else {
            List_push(result, right->first->value);
            List_shift(right);
        }
    }

    while (left->count != 0) {
        List_push(result, left->first->value);
        List_shift(left);
    }

    while (right->count != 0) {
        List_push(result, right->first->value);
        List_shift(right);
    }

    return result;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if (list->count <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    int i = 0;

    LIST_FOREACH(list, first, next, cur) {
        if (i < list->count / 2) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }
        i++;
    }

    left = List_merge_sort(left, cmp);
    right = List_merge_sort(right, cmp);

    return List_merge(left, right, cmp);
}
