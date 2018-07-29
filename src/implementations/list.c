#include "../headers/list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

List *list_init(List *list, void (*destory_data)(void *data)){
    if(NULL == list){
        if((list = malloc(sizeof *list)) == NULL) return NULL;
        list->destory_list = free;
    }
    else list->destory_list = NULL;

    list->head          = NULL;
    list->tail          = NULL;
    list->size          = 0;
    list->destory_data  = destory_data;

    return list;
}

int list_destory(List *list){
    if(NULL == list) return -1;

    void *data = NULL;
    while(list->size > 0){
        if(list_rem_next(list, NULL, (void **)&data) == 0 && list->destory_data != NULL)
            list->destory_data(data);
    }

    if(NULL == list->destory_list) memset(list, 0, sizeof(List));
    else list->destory_list(list);

    return 0;    
}

int list_ins_next(List *list, ListNode *node, const void *data){
    ListNode *new_node = NULL;
    if((new_node = malloc(sizeof *new_node)) == NULL) return -1;

    new_node->data = (void *)data;
    if(node == NULL){
        // insert at head position
        if(list->size == 0) list->tail = new_node;

        new_node->next = list->head;
        list->head = new_node;
    }else{
        // insert at other position
        if(node->next == NULL) list->tail = new_node;

        new_node->next = node->next;
        node->next = new_node;
    }

    (list->size)++;
    return 0;
}

int list_rem_next(List *list, ListNode *node, void **data){
    ListNode *old_node;

    if(list->size == 0) return -1;

    if(node == NULL){
        // remove at head position
        old_node = list->head;
        list->head = list->head->next;

        if(list->size == 1) list->tail = NULL;
    }else{
        // remove at other position
        if(node->next == NULL) return -1;

        old_node = node->next;
        node->next = node->next->next;

        if(node->next->next == NULL) list->tail = node;
    }
    if(data != NULL) *data = old_node->data;

    free(old_node);
    (list->size)--;
    return 0;
}

void list_for_each(const List *list, Print print){
    assert(print != NULL);

    for(ListNode *iter = list_head(list); iter != NULL; iter = iter->next)
        print(iter->data);
    printf("\n");
}