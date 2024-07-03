#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node* head;
    size_t size;
} LinkedList;

LinkedList* ll_build(int* keys, size_t size);
void ll_print(LinkedList* llist);
void ll_free(LinkedList* llist);
int ll_prepend(LinkedList* llist, int key);
int ll_append(LinkedList* llist, int key);
int ll_push_to(LinkedList *llist, int i, int key);
int ll_get_at(LinkedList *llist, int i);
Node* ll_get_by_key(LinkedList *llist, int key);
Node *ll_pop(LinkedList *llist, int i);
Node *ll_pop_by_key(LinkedList *llist, int key);
void ll_reverse(LinkedList *llist);

#endif // !LINKED_LIST_H
