#include "../headers/clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


CList *clist_init(CList *clist, void (*destory_data)(void *data)){
    if(clist == NULL) {
        if(clist = malloc(sizeof *clist) == NULL) return NULL;
        clist->destory_list = free;
    }
    else clist->destory_list = NULL;

    clist->size         = 0;
    clist->head         = NULL;
    clist->destory_data = destory_data;
    return clist;
}

int clist_destory(CList *clist){
    if(clist == NULL) return -1;

    void *data = NULL;
    while(clist->size > 0){
        if(clist_rem_next(clist, clist->head, (void **)&data) == 0 && clist->destory_data != NULL)
            clist->destory_data(data);
    }
    if(clist->destory_list == NULL) memset(clist, 0, sizeof(CList));
    else clist->destory_list(clist);

    return 0;
}

int clist_ins_next(CList *clist, CListNode *node, const void *data){
    if(clist == NULL) return -1;

    CListNode *new_node = NULL;
    if((new_node = malloc(sizeof *new_node)) == NULL)return -1;
    new_node->data = data;

    if(node == NULL || node->next == clist->head){
        // insert at head position
        new_node->next = clist->head;
        clist->head    = new_node;
        if(node) node->next = new_node; 
    }else{
        // insert at other position
        new_node->next = node->next;
        node->next     = new_node;
    }

    ++(clist->size);
    return 0;
}

int clist_rem_next(CList *clist, CListNode *node, void **data){
    if(clist == NULL || node == NULL) return -1;

    CListNode *old_node = NULL;

    if(node->next == clist->head){
        // remove at head position
        old_node   = clist->head;
        node->next = old_node->next;
        if(clist->size == 1) clist->head = NULL;
        else clist->head = node->next; 
    }else{
        // remove at other position
        old_node = node->next;
        node->next = old_node->next;
    }

    if(data != NULL) *data = old_node->data;
    
    free(old_node);
    --(clist->size);
    return 0;
}