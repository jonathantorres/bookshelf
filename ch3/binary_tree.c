#include "binary_tree.h"

void *find_node(binary_tree_node *node, void *value, binary_tree_cmp cmp)
{
    if (!node) {
        return NULL;
    }
    int result = cmp(node->value, value);

    if (result == 0) {
        return node->value;
    } else if (result < 0) {
        return find_node(node->left, value, cmp);
    } else if (result > 0) {
        return find_node(node->right, value, cmp);
    }

    return NULL;
}

binary_tree_node *create_node(void *value)
{
    binary_tree_node *node = malloc(sizeof(binary_tree_node));
    if (!node) {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_node(binary_tree_node **node, void *value, binary_tree_cmp cmp)
{
    if (*node == NULL) {
        binary_tree_node *new_node = create_node(value);
        *node = new_node;
        return;
    }

    if (cmp((*node)->value, value) < 0) {
        insert_node(&(*node)->left, value, cmp);
    } else {
        insert_node(&(*node)->right, value, cmp);
    }
}

void traverse_node(binary_tree_node *node, binary_tree_cb cb)
{
    if (!node) {
        return;
    }
    traverse_node(node->left, cb);
    cb(node);
    traverse_node(node->right, cb);
}

void destroy_node(binary_tree_node *node)
{
    if (!node) {
        return;
    }

    destroy_node(node->left);
    destroy_node(node->right);
    free(node);
}

binary_tree *binary_tree_new(void)
{
    binary_tree *tree = malloc(sizeof(binary_tree));

    if (!tree) {
        return NULL;
    }
    tree->len = 0;
    tree->root = NULL;

    return tree;
}

void *binary_tree_search(binary_tree *tree, void *value, binary_tree_cmp cmp)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    return find_node(tree->root, value, cmp);
}

void binary_tree_insert(binary_tree *tree, void *value, binary_tree_cmp cmp)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        binary_tree_node *node = create_node(value);
        if (!node) {
            return;
        }

        tree->root = node;
        return;
    }

    insert_node(&tree->root, value, cmp);
    return;
}

void binary_tree_traverse(binary_tree *tree, binary_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    traverse_node(tree->root, cb);
}

void binary_tree_destroy(binary_tree *tree, binary_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    binary_tree_traverse(tree, cb);
    destroy_node(tree->root);

    if (tree) {
        free(tree);
    }
}
