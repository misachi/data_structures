#include <stdio.h>
#include <stdlib.h>

#define RED 'R'
#define BLACK 'B'

struct node {
    int data;
    struct node *left, *right, *parent;
    char colour;
};

typedef struct {
    struct node *root;
    int count;
    int size;
} tree;

struct node *new_node(int key) {
    struct node *node = (struct node *)malloc(sizeof(struct node *));
    node->left = NULL;
    node->right = NULL;
    node->colour = RED;
    node->data = key;
    node->parent = NULL;
    return node;
}

tree *new_tree() {
    tree *tr = (tree *)malloc(sizeof(tree *));
    tr->count = 0;
    tr->size = 100;
    tr->root = (struct node*)calloc((size_t)tr->size, sizeof(struct node *));
    return tr;
}

void free_tree(struct node *node) {
    if (node) {
        free_tree(node->left);
        free(node);
        free_tree(node->right);
    }
}

void left_rotate(tree* tr, struct node *node) {
    struct node *y = node->right; // We assume x's right node is non-empty
    // struct node *xparent = node->parent;
    node->right = y->left;

    if (y->left)
        y->left->parent = node;

    y->parent = node->parent;

    if (!node->parent)
        tr->root = y;
    else if (node->data == node->parent->left->data)
        node->parent->left = y;
    else
        node->parent->right = y;
        // node->parent->left = y;
        // y->parent = node->parent;

    y->left = node;
    node->parent = y;
}

void right_rotate(tree *tr, struct node *node) {

}

void insert(tree *tr, int key) {
    struct node *node = new_node(key);
    struct node *root = tr->root;
    struct node *parent = NULL;

    while (root)
    {
        parent = root->parent;
        if (node->data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    node->parent = parent;
    tr->count++;
    if (!parent)
        tr->root = parent;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;
}

int main(void) {

}