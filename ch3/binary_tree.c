#include "binary_tree.h"

binary_tree_node *find_node(binary_tree_node *node, void *value, binary_tree_cmp cmp)
{
    if (!node) {
        return NULL;
    }
    int result = cmp(node->value, value);

    if (result == 0) {
        return node;
    } else if (result < 0) {
        return find_node(node->left, value, cmp);
    } else if (result > 0) {
        return find_node(node->right, value, cmp);
    }

    return NULL;
}

binary_tree_node *find_min_node(binary_tree_node *node)
{
    binary_tree_node *min_node = node;

    while (min_node->left != NULL) {
        min_node = min_node->left;
    }
    return min_node;
}

binary_tree_node *find_max_node(binary_tree_node *node)
{
    binary_tree_node *max_node = node;

    while (max_node->right != NULL) {
        max_node = max_node->right;
    }
    return max_node;
}

binary_tree_node *create_node(void *value)
{
    binary_tree_node *node = malloc(sizeof(binary_tree_node));
    if (!node) {
        return NULL;
    }

    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_node(binary_tree_node **node, binary_tree_node *parent, void *value, binary_tree_cmp cmp)
{
    if (*node == NULL) {
        binary_tree_node *new_node = create_node(value);
        new_node->parent = parent;
        *node = new_node;
        return;
    }

    if (cmp(value, (*node)->value) < 0) {
        insert_node(&(*node)->left, *node, value, cmp);
    } else {
        insert_node(&(*node)->right, *node, value, cmp);
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

    binary_tree_node *node_found = find_node(tree->root, value, cmp);
    if (!node_found) {
        return NULL;
    }

    return node_found->value;
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

    insert_node(&tree->root, tree->root, value, cmp);
    return;
}

void destroy_single_node(binary_tree_node *node, binary_tree_cb cb)
{
    if (!node) {
        return;
    }
    cb(node);
    free(node);
}

void binary_tree_delete(binary_tree *tree, void *value, binary_tree_cmp cmp, binary_tree_cb cb)
{
    if (!tree) {
        return;
    }
    if (tree->root == NULL) {
        return;
    }

    binary_tree_node *node_to_delete = find_node(tree->root, value, cmp);
    if (node_to_delete == NULL) {
        return;
    }

    // let's delete the node
    if (node_to_delete->left == NULL && node_to_delete->right == NULL) {
        // node with no children
        destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left == NULL && node_to_delete->right != NULL) {
        // node with a right child
        binary_tree_node *node_to_move = node_to_delete->right;
        node_to_move->parent = node_to_delete->parent;
        if (node_to_move->parent->right == node_to_delete) {
            node_to_move->parent->right = node_to_move;
        } else {
            node_to_move->parent->left = node_to_move;
        }
        destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != NULL && node_to_delete->right == NULL) {
        // node with a left child
        binary_tree_node *node_to_move = node_to_delete->left;
        node_to_move->parent = node_to_delete->parent;
        if (node_to_move->parent->right == node_to_delete) {
            node_to_move->parent->right = node_to_move;
        } else {
            node_to_move->parent->left = node_to_move;
        }
        destroy_single_node(node_to_delete, cb);
    } else if (node_to_delete->left != NULL && node_to_delete->right != NULL) {
        // node with left and right children
        binary_tree_node *replacement = find_min_node(node_to_delete->right);
        replacement->right = node_to_delete->right;
        replacement->left = node_to_delete->left;
        replacement->parent = node_to_delete->parent;
        replacement->right->parent = replacement;
        replacement->left->parent = replacement;
        destroy_single_node(node_to_delete, cb);
    }
}

void *binary_tree_find_min(binary_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    binary_tree_node *min_node = find_min_node(tree->root);
    if (min_node == NULL) {
        return NULL;
    }

    return min_node->value;
}

void *binary_tree_find_max(binary_tree *tree)
{
    if (!tree) {
        return NULL;
    }
    if (tree->root == NULL) {
        return NULL;
    }

    binary_tree_node *max_node = find_max_node(tree->root);
    if (max_node == NULL) {
        return NULL;
    }

    return max_node->value;
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
