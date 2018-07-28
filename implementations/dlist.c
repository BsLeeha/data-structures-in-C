#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../headers/dlist.h"

DList *dlist_init(DList *dlist, void (*destory_data)(void *data)){
    if(dlist == NULL) {
        if(dlist = malloc(sizeof *dlist) == NULL) return -1;
        dlist->destory_list = free;
    }else dlist->destory_list = NULL;
    
    dlist->size         = 0;
    dlist->destory_data = destory_data;
    dlist->head         = NULL;
    dlist->tail         = NULL;

    return 0;
}

int dlist_destory(DList *dlist){
    if(dlist == NULL) return -1;

    void *data = NULL;
    while(dlist->size > 0){
        if(dlist_rem_next(dlist, NULL, (void **)&data) == 0 && dlist->destory_data != NULL)
            dlist->destory_data(data);
    }

    if(dlist->destory_list == NULL) memset(dlist, 0, sizeof *dlist);
    else dlist->destory_list(dlist);

    return 0;
}

int dlist_ins_next(DList *dlist, DListNode *node, const void *data){
    if(dlist == NULL) return -1;

    DListNode *new_node = NULL;
    if((new_node = malloc(sizeof *new_node)) == NULL) return NULL;
    new_node->data = data;

    if(node == NULL){
        // insert at head position
        new_node->prev = NULL;
        new_node->next = dlist->head;
        dlist->head = new_node;
        
        if(new_node->next == NULL) dlist->tail = new_node;
        else new_node->next->prev = new_node;
    }else{
        // insert at other position
        new_node->prev = node;
        new_node->next = node->next;
        node->next = new_node;

        if(new_node->next == NULL) dlist->tail = new_node;
        else new_node->next->prev = new_node;
    }
    
    (dlist->size)++;

    return 0;
}

int dlist_ins_prev(DList *dlist, DListNode *node, const void *data){
    if(dlist == NULL) return -1;

    DListNode *new_node =  NULL;
    if((new_node = malloc(sizeof *new_node)) == NULL) return NULL;
    new_node->data = data;

    if(node == NULL){
        // insert at tail position
        new_node->next = NULL;
        new_node->prev = dlist->tail;
        dlist->tail    = new_node;

        if(new_node->prev == NULL) dlist->head = new_node;
        else new_node->prev->next = new_node;
    }else{
        // insert at other position
        new_node->next = node;
        new_node->prev = node->prev;
        node->prev     = new_node;

        if(new_node->prev == NULL) dlist->head = new_node;
        else new_node->prev->next = new_node;
    }

    (dlist->size)++;
    return 0;
}

int dlist_remove(DList *dlist, DListNode *node, void **data){
    if(dlist == NULL || dlist->head == NULL) return -1;

    DListNode *old_node = node;
    *data = node->data;

    if(node = dlist->head){
        // remove at head position
        if((dlist->head = node->next)== NULL) dlist->tail = NULL;
        else dlist->head->prev = NULL;
    }else{
        // remove at other position
        if((node->prev->next = node->next) == NULL) dlist->tail = node->prev;
        else node->next->prev = node->prev;
    }

    free(node);
    (dlist->size)--;
    return 0;
}