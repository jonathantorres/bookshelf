#ifndef _binary_tree_h
#define _binary_tree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct binary_tree_node {
    // struct binary_tree_node *parent;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
    void *value;
} binary_tree_node;

typedef struct binary_tree {
    binary_tree_node *root;
    int len;
} binary_tree;

typedef void (*binary_tree_cb)(binary_tree_node *node);
typedef int (*binary_tree_cmp)(void *a, void *b);

binary_tree *binary_tree_new(void);
void binary_tree_insert(binary_tree *tree, void *value, binary_tree_cmp cmp);
void binary_tree_delete(binary_tree *tree, void *value, binary_tree_cmp cmp, binary_tree_cb cb);
void *binary_tree_search(binary_tree *tree, void *value, binary_tree_cmp cmp);
void *binary_tree_find_max(binary_tree *tree);
void *binary_tree_find_min(binary_tree *tree);
void binary_tree_traverse(binary_tree *tree, binary_tree_cb cb);
void binary_tree_destroy(binary_tree *tree, binary_tree_cb cb);

#endif
