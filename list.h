#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

// Связные списки 

struct list {
    void *data;
    struct list *next;
};

struct list *list_add(struct list *head, void *new_item);

void list_print(struct list *head);

void list_traverse(struct list *head, void (*callback)(void *));

void list_free(struct list *head, void (*free_data)(void*));

#endif