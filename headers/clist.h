#ifndef CLIST_H
#define CLIST_H

// structure for ciucular linked list elems
typedef struct CListElem_{
    void              *data;
    struct CListElem_ *next;
}CListElem;

// structure for circular linked lists
typedef struct CList_{
    int        size;
    CListElem *head;

    // if data is dynamically allocated, then we need to free it (or not), that dependes on the user
    void      (*destory)(void *data);           
    void      (*match)(const void *key1, const void *key2);
}CList;

// public interface
int clist_init(CList **clist, void (*destory)(void *data));

// call clist_rem_next to destory next elem, and destory data
int clist_destory(CList *clist); 

int clist_ins_next(CList *clist, CListElem *elem, const void *data);

// destory next elem, but not on data
int clist_rem_next(CList *clist, CListElem *elem, void **data); 

#define clist_size(clist) ((clist)->size)

#define clist_head(clist) ((clist)->head)

#define clist_is_head(clist, elem) ((elem == (clist)->head) ? 1 : 0)

#define elem_data(elem) ((elem)->data)

#define elem_next(elem) ((elem)->next)

#endif // CLIST_H
