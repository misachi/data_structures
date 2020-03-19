#include <stdio.h>
#include <stdlib.h>

struct hash_item {
    int key;
    int value;
    struct hash_item *next, *prev;
};

struct hash_table {
    int size;
    int count;
    struct hash_item **items;
};

struct hash_item *new_item(int key, int value) {
    struct hash_item *item = malloc(sizeof(struct hash_item));
    item->key = key;
    item->value = value;
    item->prev = item->next = NULL;
    return item;
}

struct hash_table *new_table() {
    struct hash_table *tbl = malloc(sizeof(struct hash_table));
    tbl->size = 150;
    tbl->count = 0;
    tbl->items = calloc((size_t)tbl->size, sizeof(struct hash_item*));
    return tbl;
}

int hash_function(int key) {
    return key % 51;
}

void ht_insert(struct hash_table *ht, int key, int value) {
    int hash = hash_function(key);
    struct hash_item *item_ = new_item(key, value);
    struct hash_item *items = ht->items[hash];

    ht->count++;
    if (items == NULL) {
        items = item_;
    } else {
        item_->next = items;
    }
    ht->items[hash] = item_;
}

int search(struct hash_table *ht, int key) {
    int hash = hash_function(key);
    struct hash_item *items = ht->items[hash];

    while (items)
    {
        if (key == items->key)
        {
            return items->value;
        }
        items = items->next;
    }
    return -1;
}

void free_hash_item(struct hash_item *item) {
    free(item->next);
    free(item->prev);
    free(item);
}

void free_hash_table(struct hash_table *ht) {
    for(int i=0; i < ht->size; i++) {
        struct hash_item *items = ht->items[i];
        if (items)
            free_hash_item(items);
    }

    free(ht->items);
    free(ht);
}

int main(void) {
    struct hash_table *ht = new_table();
    ht_insert(ht, 1, 2);
    ht_insert(ht, 3, 5);
    ht_insert(ht, 10, 4);

    printf("Count: %d Value: %d\n", ht->count, search(ht, 10));

    free_hash_table(ht);
}