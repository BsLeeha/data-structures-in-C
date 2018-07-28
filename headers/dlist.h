#ifndef DIST_H
#define DIST_H

typedef struct DListElem_{
    void              *data;
    struct DListElem_ *prev;
    struct DListElem_ *next;
}DistElem;


typedef struct DList_{
    int      size;

    void     (*destory)(void *data);
    void     (*match)(const void *key1, const void *key2);

    DistElem *head;
    DistElem *tail;
}DList_;

/* public interfaces */

Dlist *dlist_init(DList *dlist, void (*destory)(void *data));

int dlist_destory(DList *dlist);

int dlist_ins_prev(DList *dlist, DListElem *elem, const void *data);

int dlist_ins_next(DList *dlist, DListElem *elem, const void *data);

int dlist_remove(DList *dlist, DListElem *elem, void **data);

#define dlist_size(dlist) ((dlist)->size)

#define dlist_head(dlist) ((dlist)->head)

#define dlist_tail(dlist) ((dlist)->tail)

#define dlist_is_head(dlist, elem) ((elem == (dlist)->head) ? 1 : 0)

#define dlist_is_tail(dlist, elem) ((elem == (dlist)->tail) ? 1 : 0)

#define elem_data(elem) ((elem)->data)

#define elem_prev(elem) ((elem)->prev)

#define elem_next(elem) ((elem)->next)

#endif // DIST_H