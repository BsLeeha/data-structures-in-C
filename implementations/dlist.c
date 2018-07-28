#include "dlist.h"

int dlist_init(DList **dlist, void (*destory)(void *data)){
    if(dlist == NULL) return -1;
    if(*dlist == NULL) 
        if(*dlist = (Dlist *)malloc(sizeof(Dlist)) == NULL) return -1;
    
    (*dlist)->size = 0;
    (*dlist)->destory = destory;
    (*dlist)->head = NULL;
    (*dlist)->tail = NULL;

    return 0;
}

int dlist_destory(DList *dlist){
    if(dlist == NULL) return -1;

    void *data = NULL;
    while(dlist->size > 0){
        if(dlist_rem_next(dlist, NULL, (void **)&data) == 0 && dlist->destory != NULL)
            dlist->destory(data);
    }

    memset(dlist, 0, sizeof(Dlist));

    return 0;
}

int dlist_ins_next(DList *dlist, DListElem *elem, const void *data){
    if(dlist == NULL) return -1;

    DListElem *new_elem = (DListElem *)malloc(sizeof(DListElem));
    new_elem->data = data;

    if(elem == NULL){
        // insert at head position
        new_elem->prev = NULL;
        new_elem->next = dlist->head;
        dlist->head = new_elem;
        
        if(new_elem->next == NULL) dlist->tail = new_elem;
        else new_elem->next->prev = new_elem;
    }else{
        // insert at other position
        new_elem->prev = elem;
        new_elem->next = elem->next;
        elem->next = new_elem;

        if(new_elem->next == NULL) dlist->tail = new_elem;
        else new_elem->next->prev = new_elem;
    }
    
    (dlist->size)++;

    return 0;
}

int dlist_ins_prev(DList *dlist, DListElem *elem, const void *data){
    if(dlist == NULL) return -1;

    DListElem *new_elem = (DListElem *)malloc(sizeof(DListElem));
    new_elem->data = data;

    if(elem == NULL){
        // insert at tail position
        new_elem->next = NULL;
        new_elem->prev = dlist->tail;
        dlist->tail    = new_elem;

        if(new_elem->prev == NULL) dlist->head = new_elem;
        else new_elem->prev->next = new_elem;
    }else{
        // insert at other position
        new_elem->next = elem
        new_elem->prev = elem->prev;
        elem->prev     = new_elem;

        if(new_elem->prev == NULL) dlist->head = new_elem;
        else new_elem->prev->next = new_elem;
    }

    (dlist->size)++;
    return 0;
}

int dlist_remove(DList *dlist, DListElem *elem, void **data){
    if(dlsit == NULL || dlist->head == NULL) return -1;

    DListElem *old_elem = elem;
    *data = elem->data;

    if(elem = dlist->head){
        // remove at head position
        if((dlist->head = elem->next)== NULL) dlist->tail = NULL;
        else dlist->head->prev = NULL;
    }else{
        // remove at other position
        if((elem->prev->next = elem->next) == NULL) dlist->tail = elem->prev;
        else elem->next->prev = elem->prev;
    }

    free(elem);
    (dlist->size)--;
    return 0;
}