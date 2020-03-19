#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node *left, *right, *parent;
};

struct tree
{
    struct node *root;
    int size;
};

struct node *new_node(int item) {
    struct node *_node = (struct node*)malloc(sizeof(struct node));
    _node->data = item;
    _node->left = _node->right = _node->parent = NULL;
    return _node;
}

void in_order_traversal(struct node *Tree) {
    if (NULL != Tree) {
        in_order_traversal(Tree->left);
        if (Tree->parent != NULL)
            printf("Parent: %d\n", Tree->parent->data);
        printf("Child: %d\n", Tree->data);
        printf("\n");
        in_order_traversal(Tree->right);
    }
}

void clean_up(struct node *root) {
    if (root != NULL) {
        clean_up(root->left);
        free(root);
        clean_up(root->right);
    }
}

struct node *insert(struct node* node_, int item) {
    if (NULL == node_)
        return new_node(item);

    if (item < node_->data) {
        node_->left = insert(node_->left, item);
        node_->left->parent = node_;
    } else {
        node_->right = insert(node_->right, item);
        node_->right->parent = node_;
    }
    return node_;
}

bool tree_search(struct node *node, int item) {
    while ((node != NULL) && (item != node->data))
    {
        if (item < node->data)
            node = node->left;
        else
            node = node->right;
    }

    if (!node)
        return false;
    return item == node->data;
}

struct node *tree_maintain(struct tree *Tree, int item) {
    Tree->size++;
    return insert(Tree->root, item);
}

void insert_iterative(struct tree *Tree, int item) {
    struct node *node = new_node(item);
    struct node *y = NULL;
    struct node *root = Tree->root;

    while (root != NULL)
    {
        y = root;
        if (item < root->data)
            root = root->left;
        else
            root = root->right;
    }

    node->parent = y;
    Tree->size++;
    if (y == NULL)
        Tree->root = node;
    else if (item < y->data)
        y->left = node;
    else
        y->right = node;
}

int main(void) {
    struct tree *Tree = (struct tree *)malloc(sizeof(struct tree));
    Tree->root = NULL;
    Tree->size = 0;

    // Tree->root = tree_maintain(Tree, 2);
    // tree_maintain(Tree, 1);
    // tree_maintain(Tree, 4);
    // tree_maintain(Tree, 0);
    // tree_maintain(Tree, 7);
    // tree_maintain(Tree, 3);

    insert_iterative(Tree, 2);
    insert_iterative(Tree, 1);
    insert_iterative(Tree, 4);
    insert_iterative(Tree, 0);
    insert_iterative(Tree, 7);
    insert_iterative(Tree, 3);

    in_order_traversal(Tree->root);
    printf("\n");
    printf("Root: %d\n", Tree->root->data);
    printf("Size: %d\n", Tree->size);
    printf("Found: %d\n", tree_search(Tree->root, 2));
    clean_up(Tree->root);
    free(Tree->root);
    free(Tree);
}
