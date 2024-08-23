#include "clist.h"
#include <stdlib.h>

int clist_is_empty(struct clist *list) {
    return ((list->first == list->last) && (list->first == NULL));
}

struct clist *clist_new(void) {
    struct clist *list = malloc(sizeof(struct clist));
    if (!list)
        return NULL;

    list->first = list->last = NULL;
    list->count = 0;
    return list;
}

int clist_append(struct clist *list, void *data) {
    if (!list)
        return -1;
    return clist_insert_after(list, list->last, data);
}

int clist_prepend(struct clist *list, void *data) {
    if (!list)
        return -1;
    return clist_insert_before(list, list->first, data);
}

int clist_insert_before(struct clist *list, struct clist_cell *cell, void *data) {
    struct clist_cell *new_cell;

    new_cell = malloc(sizeof(struct clist_cell));
    if (!new_cell) {
        return -1;
    }

    new_cell->data = data;
    list->count++;

    if (clist_is_empty(list)) {
        new_cell->prev = new_cell->next = NULL;
        list->first = list->last = new_cell;
        return 0;
    }

    // If we are not provided with a cell as a reference, the new cell will be
    // added before the last element of the list.
    if (!cell) {
        cell = list->last;
    }

    new_cell->prev = cell->prev;
    new_cell->next = cell;
    if (!cell->prev) {
        list->first = new_cell;
    } else {
        cell->prev->next = new_cell;
    }
    cell->prev = new_cell;
    return 0;
}

int clist_insert_after(struct clist *list, struct clist_cell *cell,
                       void *data) {
    struct clist_cell *new_cell;

    if (!list)
        return -1;

    new_cell = malloc(sizeof(struct clist_cell));
    if (!new_cell)
        return -1;

    new_cell->data = data;
    list->count++;

    if (clist_is_empty(list)) {
        new_cell->prev = new_cell->next = NULL;
        list->first = list->last = new_cell;
        return 0;
    }

    // If we are not provided with a cell as a reference, the new cell will be
    // added after the last element of the list.
    if (!cell) {
        cell = list->last;
    }

    new_cell->prev = cell;
    new_cell->next = cell->next;
    if (!cell->next) {
        list->last = new_cell;
    } else {
        cell->next->prev = new_cell;
    }
    cell->next = new_cell;
    return 0;
}

int clist_delete(struct clist *list, struct clist_cell *cell) {
    if (!list)
        return -1;
    if (!cell)
        return 0;

    if (cell->prev) {
        cell->prev->next = cell->next;
    } else {
        // `cell` was the first element of the list
        cell->next->prev = NULL;
        list->first = cell->next;
    }

    if (cell->next) {
        cell->next->prev = cell->prev;
    } else {
        // `cell` was the last element of the list
        cell->prev->next = NULL;
        list->last = cell->prev;
    }

    free(cell);
    list->count--;

    return 0;
}

void clist_free(struct clist *list) {
    struct clist_cell *cell, *next;

    if (!list) return;

    cell = list->first;
    while (cell) {
        next = cell->next;
        free(cell);
        cell = next;
    }
    free(list);
}
