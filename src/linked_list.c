#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList* ll_build(int* keys, size_t size) {
    LinkedList *llist = malloc(sizeof(LinkedList));
    if (llist == NULL) {
        printf("ll_build :: Memory allocation for llist failed. Cannot create a linked list\n");
        return NULL;
    }

    if (keys == NULL || size == 0) {
        llist->size = 0;
        llist->head = NULL;
        return llist;
    }

    Node *head        = NULL;
    Node *last_node   = NULL;

    for (int i = 0; i < (int)size; i++) {
        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            return NULL;
        }
        new_node->key  = keys[i];
        new_node->next = NULL;

        if (last_node != NULL) {
            last_node->next = new_node;
        } else {
            head = new_node;
        }
        last_node = new_node;
    }

    llist->head = head;
    llist->size = size;

    return llist;
}

void ll_print(LinkedList* llist) {
    if (llist == NULL) {
        printf("LinkedList()");
        return;
    }
    Node* current_node = llist->head;
    printf("LinkedList(");
    while (current_node != NULL) {
        printf("%d", current_node->key);
        if (current_node->next != NULL) {
            printf("->");
        }
        current_node = current_node->next;
    }
    printf(")\n");
}

void ll_free(LinkedList* llist) {
    Node* current_node = llist->head;
    while (current_node != NULL) {
        Node *next = current_node->next;
        free(current_node);
        current_node = next;
    }
    free(llist);
}

int ll_prepend(LinkedList* llist, int key) {
    if (llist == NULL) {
        return -1;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("ll_prepend :: Memory allocation for new_node failed. Cannot prepend a new node to llist.\n");
        return -1;
    }

    new_node->key = key;
    new_node->next = llist->head;
    llist->head = new_node;
    llist->size++;
    return 0;
}

int ll_append(LinkedList* llist, int key) {
    if (llist == NULL) {
        return -1;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("ll_append :: Memory allocation for new_node failed. Cannot append a new node to llist.\n");
        return -1;
    }

    Node *current_node = llist->head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    new_node->key = key;
    new_node->next = NULL;
    current_node->next = new_node;
    llist->size++;

    return 0;
}

int ll_push_to(LinkedList *llist, int i, int key) {
    if (llist == NULL) {
        return -1;
    }
    
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("ll_push_to :: Memory allocation for new_node failed. Cannot push new node to llist.\n");
        return -1;
    }

    Node *current_node = llist->head;
    for (int j = 0; j < i - 1; j++) {
        if (current_node->next == NULL) {
            break;
        }
        current_node = current_node->next;
    }

    new_node->key = key;
    new_node->next = current_node->next;
    current_node->next = new_node;
    llist->size++;

    return 0;
}

int ll_get_at(LinkedList *llist, int i) {
    if (llist == NULL) {
        return -1;
    }

    int current_index = 0;
    Node *current_node = llist->head;
    while (current_node != NULL) {
        if (current_index == i) {
            return current_node->key;
        }
        current_node = current_node->next;
        current_index++;
    }
    return -1;
}

Node* ll_get_by_key(LinkedList *llist, int key) {
    if (llist == NULL) {
        return NULL;
    }

    Node *current_node = llist->head;
    while (current_node != NULL) {
        if (current_node->key == key) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

Node *ll_pop(LinkedList *llist, int i) {
    if (llist == NULL) {
        return NULL;
    }

    Node *prev_node = NULL;
    Node *current_node = llist->head;
    for (int j = 0; j < i; j++) {
        if (current_node == NULL) {
            break;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (prev_node == NULL) {
        llist->head = current_node->next;
    } else {
        prev_node->next = current_node->next;
    }

    current_node->next = NULL;
    llist->size--;
    return current_node;
}

Node *ll_pop_by_key(LinkedList *llist, int key) {
    if (llist == NULL) {
        return NULL;
    }

    Node *current_node = llist->head;
    Node *prev_node = NULL;
    while (current_node != NULL) {
        if (current_node->key == key) {
            break;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }
    if (prev_node == NULL) {
        llist->head = current_node->next;
    } else {
        prev_node->next = current_node->next;
    }
    current_node->next = NULL;
    llist->size--;
    return current_node;
}

void ll_reverse(LinkedList *llist) {
    if (llist == NULL) {
        return;
    }

    Node *prev_node = NULL;
    Node *current_node = llist->head;
    Node *next_node = NULL;
    while (current_node != NULL) {
        next_node = current_node->next;
        current_node->next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }
    llist->head = prev_node;
}

