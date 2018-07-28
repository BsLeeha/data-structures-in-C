#include "../headers/clist.h"

int clist_init(CList **clist, void (*destory)(void *data)){
    if(clist == NULL) return -1;
    if(*clist == NULL) *clist = (Clist *)malloc(sizeof(Clist));
    
    clist->size    = 0;
    clist->head    = NULL;
    clist->destory = destory;
    return 0;
}

int clist_destory(CList *clist){
    if(clist == NULL) return -1;

    void *data = NULL;
    while(clist->size > 0){
        if(clist_rem_next(clist, clist->head, (void **)&data) == 0 && clist->destory != NULL)
            clist->destory(data);
    }
    memset(clist, 0, sizeof(CList));

    return 0;
}

int clist_ins_next(CList *clist, CListElem *elem, const void *data){
    if(clist == NULL) return -1;

    CListElem *new_elem = (CListElem *)malloc(sizeof(CListElem));
    new_elem->data = data;
    if(elem == NULL || elem->next == clist->head){
        // insert at head position
        if(elem == NULL) {      // no elements
            clist->head    = new_elem;
            new_elem->next = clist->head;
        }
        else{                   // have elements
            elem->next     = new_elem;
            new_elem->next = clist->head;
            clist->head    = new_elem;
        }
    }else{
        // insert at other position
        new_elem->next = elem->next;
        elem->next     = new_elem;
    }

    (clist->size)++;
    return 0;
}

int clist_rem_next(CList *clist, CListElem *elem, void **data){
    if(clist == NULL || elem == NULL) return -1;

    CListElem *old_elem = NULL;

    if(elem->next == clist->head){
        // remove at head position
        old_elem   = clist->head;
        elem->next = old_elem->next;
        if(clist->size == 1) clist->head = NULL
        else clist->head = elem->next; 
    }else{
        // remove at other position
        old_elem = elem->next;
        elem->next = old_elem->next;
    }

    if(data != NULL) *data = old_elem->data;
    
    free(old_elem);
    (clist->size)--;
    return 0;
}