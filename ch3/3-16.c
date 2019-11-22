/**
 * 3-16 - Implement versions of several different dictionary data structures, such as linked lists, binary trees, balanced binary search trees, and hash tables. Conduct experiments to assess the relative performance of these data structures in a simple application that reads a large text file and reports exactly one instance of each word that appears within it.
 * This application can be efficiently implemented by maintaining a dictionary of all distinct words that have appeared thus far in the text and inserting/reporting each word that is not found. Write a brief report with your conclusions.
 */
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "array.h"
#include "hash_table.h"
#include "binary_tree.h"

int hash_table_cmp(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

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
    printf("node val: %d\n", *(int *)node->value);
}

void binary_tree_delete_cb(binary_tree_node *node)
{
    if (node) {
        // nothing to free here
    }
}

int main(void)
{
    int num1 = 10;
    int num2 = 3;
    int num3 = 43;
    int num4 = 12;
    int s1 = 10;
    binary_tree *tree = binary_tree_new();
    binary_tree_insert(tree, &num1, binary_tree_cmp_fn);
    binary_tree_insert(tree, &num2, binary_tree_cmp_fn);
    binary_tree_insert(tree, &num3, binary_tree_cmp_fn);
    binary_tree_insert(tree, &num4, binary_tree_cmp_fn);
    binary_tree_traverse(tree, binary_tree_cb_fn);

    int *result = binary_tree_search(tree, &s1, binary_tree_cmp_fn);
    if (result == NULL) {
        printf("%d was not found!\n", s1);
    } else {
        printf("%d found!\n", *result);
    }

    int *min_val = binary_tree_find_min(tree);
    printf("min value is: %d\n", *min_val);
    int *max_val = binary_tree_find_max(tree);
    printf("max value is: %d\n", *max_val);
    binary_tree_destroy(tree, binary_tree_delete_cb);
    puts("");

    linked_list *list = linked_list_new();
    linked_list_push(list, strdup("Hola"));
    linked_list_push(list, strdup("my nombre"));
    linked_list_push(list, strdup("es"));
    linked_list_push(list, strdup("Jonathan"));
    LINKED_LIST_FOREACH(list) {
        printf("%s\n", (char*)cur->value);
    }
    puts("");

    int _num1 = 100;
    int _num2 = 101;
    int _num3 = 102;
    array *ar = array_create(10, sizeof(int));
    array_push(ar, &_num1);
    array_push(ar, &_num2);
    array_push(ar, &_num3);
    ARRAY_FOREACH(ar) {
        int *val = array_get(ar, i);
        printf("%d\n", *val);
    }
    puts("");

    hash_table *t = hash_table_create(hash_table_cmp);
    hash_table_set(t, "key1", "val1");
    hash_table_set(t, "key2", "val2");
    hash_table_set(t, "key3", "val3");
    HASH_TABLE_FOREACH(t) {
        printf("%s:%s\n", (char*)elem->key, (char*)elem->value);
    } HASH_TABLE_FOREACH_END
    return 0;
}
