/**
 * 3-21. Write a function to compare whether two binary trees are identical. Identical trees have the same key value at each position and the same structure.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "binary_tree.h"

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

bool same_trees(binary_tree *tree1, binary_tree *tree2)
{
    bool same = true;

    if (tree1->len != tree2->len) {
        same = false;
        return same;
    }

    if (tree1->root == NULL || tree2->root == NULL) {
        same = false;
        return same;
    }

    binary_tree_node *cur_tree1_node = tree1->root;
    binary_tree_node *cur_tree2_node = tree2->root;

    // check first node
    if (*(int*)cur_tree1_node->value != *(int*)cur_tree2_node->value) {
        same = false;
        return same;
    }

    // check left nodes
    while (cur_tree1_node->left != NULL && cur_tree2_node->left != NULL) {
        cur_tree1_node = cur_tree1_node->left;
        cur_tree2_node = cur_tree2_node->left;

        if (*(int*)cur_tree1_node->value != *(int*)cur_tree2_node->value) {
            same = false;
            break;
        }
    }

    // check right nodes
    cur_tree1_node = tree1->root;
    cur_tree2_node = tree2->root;
    while (cur_tree1_node->right != NULL && cur_tree2_node->right != NULL) {
        cur_tree1_node = cur_tree1_node->right;
        cur_tree2_node = cur_tree2_node->right;

        if (*(int*)cur_tree1_node->value != *(int*)cur_tree2_node->value) {
            same = false;
            break;
        }
    }

    return same;
}

int main(void)
{
    int num1 = 10;
    int num2 = 3;
    int num3 = 43;
    int num4 = 12;
    binary_tree *tree1 = binary_tree_new();
    binary_tree_insert(tree1, &num1, binary_tree_cmp_fn);
    binary_tree_insert(tree1, &num2, binary_tree_cmp_fn);
    binary_tree_insert(tree1, &num3, binary_tree_cmp_fn);
    binary_tree_insert(tree1, &num4, binary_tree_cmp_fn);
    // binary_tree_traverse(tree1, binary_tree_cb_fn);
    // puts("");

    int num5 = 10;
    int num6 = 3;
    int num7 = 43;
    int num8 = 12;
    binary_tree *tree2 = binary_tree_new();
    binary_tree_insert(tree2, &num5, binary_tree_cmp_fn);
    binary_tree_insert(tree2, &num6, binary_tree_cmp_fn);
    binary_tree_insert(tree2, &num7, binary_tree_cmp_fn);
    binary_tree_insert(tree2, &num8, binary_tree_cmp_fn);
    // binary_tree_traverse(tree2, binary_tree_cb_fn);
    // puts("");

    bool check_trees = same_trees(tree1, tree2);
    if (check_trees) {
        puts("tree 1 and tree 2 are the same");
    } else {
        puts("tree 1 and tree 2 are the NOT same");
    }


    int num10 = 10;
    int num11 = 3;
    int num12 = 9;
    int num13 = 12;
    binary_tree *tree3 = binary_tree_new();
    binary_tree_insert(tree3, &num10, binary_tree_cmp_fn);
    binary_tree_insert(tree3, &num11, binary_tree_cmp_fn);
    binary_tree_insert(tree3, &num12, binary_tree_cmp_fn);
    binary_tree_insert(tree3, &num13, binary_tree_cmp_fn);
    // binary_tree_traverse(tree3, binary_tree_cb_fn);
    // puts("");

    check_trees = same_trees(tree2, tree3);
    if (check_trees) {
        puts("tree 2 and tree 3 are the same");
    } else {
        puts("tree 2 and tree 3 are the NOT same");
    }

    // clean up
    binary_tree_destroy(tree1, binary_tree_delete_cb);
    binary_tree_destroy(tree2, binary_tree_delete_cb);
    binary_tree_destroy(tree3, binary_tree_delete_cb);

    return 0;
}
