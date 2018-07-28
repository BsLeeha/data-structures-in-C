#pragma once
#include <stdio.h>

/* singly linked list */

// ListNode dynamically allocated and freed it in program
// List and node data allocated and freed by user
typedef struct ListNode_{
    void              *data;
    struct ListNode_  *next;
}ListNode;

typedef struct{
    ListNode  *head;
    ListNode  *tail;

    int       size;
    
    void      (*destory_list)(void *list);    
    void      (*destory_data)(void *data);
    // for set implementation
    int       (*match)(const void *key1, const void *key2);
}List;

typedef void (*Print) (const void *data);

/* public interface */

List *list_init(List *list, void (*destory_data)(void *data));

int list_destory(List *list);

int list_ins_next(List *list, ListNode *node, const void *data);

#define list_append(list, data) list_ins_next(list, list_tail(list), data)

#define list_prepend(list, data) list_ins_next(list, NULL, data)

int list_rem_next(List *list, ListNode *node, void **data);

void list_for_each(const List *list, Print print);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, node) ((node == (list)->head) ? 1 : 0)

#define list_is_tail(list, node) ((node == (list)->tail) ? 1 : 0)

#define node_data(node) ((node)->data)

#define node_next(node) ((node)->next)
