#ifndef CLIST_H

struct clist_cell {
    void *data;
    struct clist_cell *prev;
    struct clist_cell *next;
};

struct clist {
    struct clist_cell *first;
    struct clist_cell *last;
    int count;
};

int clist_is_empty(struct clist *list);

struct clist *clist_new(void);

void clist_free(struct clist *list);

int clist_insert_before(struct clist *list, struct clist_cell *cell,
                        void *data);

int clist_insert_after(struct clist *list, struct clist_cell *cell, void *data);

int clist_delete(struct clist *list, struct clist_cell *cell);

int clist_append(struct clist *list, void *data);

int clist_prepend(struct clist *list, void *data);

#endif // !CLIST_H
