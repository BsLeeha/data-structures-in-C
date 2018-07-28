#ifndef CLIST_H
#define CLIST_H

typedef struct CListNode_{
    void              *data;
    struct CListNode_ *next;
}CListNode;

typedef struct CList_{
    int        size;
    CListNode *head;

    void      (*destory_list)(void *tree);
    void      (*destory_data)(void *data);           
    void      (*match)(const void *key1, const void *key2);
}CList;

/* public interface */
CList *clist_init(CList *clist, void (*destory_data)(void *data));

int clist_destory(CList *clist); 

int clist_ins_next(CList *clist, CListNode *node, const void *data);

int clist_rem_next(CList *clist, CListNode *node, void **data); 

#define clist_size(clist) ((clist)->size)

#define clist_head(clist) ((clist)->head)

#define clist_is_head(clist, node) ((node == (clist)->head) ? 1 : 0)

#endif // CLIST_H
