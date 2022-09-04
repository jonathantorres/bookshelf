/**
 * 3-22 - Write a program to convert a binary search tree into a linked list.
 */
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "binary_tree.h"

linked_list *list = NULL;

int binary_tree_cmp_fn(void *a, void *b)
{
    if (*(int*)a < *(int*)b) {
        return -1;
    } else if (*(int*)a > *(int*)b) {
        return 1;
    } else {
        return 0;
    }
}

void binary_tree_cb_fn(binary_tree_node *node)
{
    int *new_num = malloc(sizeof(int));
    *new_num = *(int*)node->value;
    linked_list_push(list, new_num);
}

void binary_tree_delete_cb(binary_tree_node *node)
{
    if (node) {
        // nothing to free here
    }
}

int main(void)
{
    list = linked_list_new();

    int num1 = 10;
    int num2 = 3;
    int num3 = 43;
    int num4 = 12;
    binary_tree *tree = binary_tree_new();
    binary_tree_insert(tree, &num1, binary_tree_cmp_fn);
    binary_tree_insert(tree, &num2, binary_tree_cmp_fn);
    binary_tree_insert(tree, &num3, binary_tree_cmp_fn);
    binary_tree_insert(tree, &num4, binary_tree_cmp_fn);
    binary_tree_traverse(tree, binary_tree_cb_fn);
    binary_tree_destroy(tree, binary_tree_delete_cb);

    LINKED_LIST_FOREACH(list) {
        printf("%d\n", *(int*)cur->value);
    }
    linked_list_destroy(list);
    return 0;
}
