#pragma once

/* doubly linked list */

typedef struct DListNode_{
    void              *data;
    struct DListNode_ *prev;
    struct DListNode_ *next;
}DListNode;


typedef struct DList_{
    int      size;

    void     (*destory_list)(void *list);
    void     (*destory_data)(void *data);
    void     (*match)(const void *key1, const void *key2);

    DListNode *head;
    DListNode *tail;
}DList;

/* public interfaces */

DList *dlist_init(DList *dlist, void (*destory_data)(void *data));

int dlist_destory(DList *dlist);

int dlist_ins_prev(DList *dlist, DListNode *node, const void *data);

int dlist_ins_next(DList *dlist, DListNode *node, const void *data);

int dlist_remove(DList *dlist, DListNode *node, void **data);

#define dlist_size(dlist) ((dlist)->size)

#define dlist_head(dlist) ((dlist)->head)

#define dlist_tail(dlist) ((dlist)->tail)

#define dlist_is_head(dlist, node) ((node == (dlist)->head) ? 1 : 0)

#define dlist_is_tail(dlist, node) ((node == (dlist)->tail) ? 1 : 0)

#define node_data(node) ((node)->data)

#define node_prev(node) ((node)->prev)

#define node_next(node) ((node)->next)
