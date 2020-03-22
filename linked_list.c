#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next, *prev;
};

struct list {
    struct node *root;
    int size;
    int count;
};

struct node *new_node(int num) {
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->data = num;
    node->next = node->prev = NULL;
    return node;
}

void insert(struct list *list, int num) {
    struct node *node = new_node(num);
    list->count++;
    node->next = list->root;
    if (list->root != NULL)
        list->root->prev = node;
    list->root = node;
}

struct node *search(struct list *list, int num) {
    struct node *node = list->root;

    while (node)
    {
        if (num == node->data) {
            return node;
        }
        node = node->next;
    }
    return node;
}

void delete_item(struct list *list, int num) {
    struct node *node = search(list, num);
    if (!node)
        return; // Item does not exist

    if (node->prev)
        node->prev->next = node->next;
    else
        list->root = node->next;

    if (node->next)
        node->next->prev = node->prev;

    free(node);
    list->count--; // Decrease count by 1
}

void clean_up(struct list *list) {
    struct node *node = list->root;
    while (node)
    {
        free(node);
        node = node->next;
    }
    free(list);
}

void list_traverse(struct node *node) {
    while (node)
    {
        printf("%d\n", node->data);
        node = node->next;
    }
}

int main(void) {
    struct list *list = (struct list*)malloc(sizeof(struct list));
    list->count = 0;
    list->size = 50;
    list->root = NULL;

    insert(list, 1);
    insert(list, 3);
    insert(list, 2);

    delete_item(list, 2);
    struct node* node = search(list, 2);
    printf("Found: %d\n", (node) ? node->data : -1);
    printf("Traversing...\n");
    list_traverse(list->root);
    printf("Size: %d\n", list->count);
    clean_up(list);
    return 0;
}