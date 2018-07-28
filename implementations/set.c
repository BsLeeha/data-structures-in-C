#include "../headers/set.h"

Set *set_init(Set *set, int (*match)(const void *key1, const void *key2), 
                       void (*destory)(void *data)){
    if((set = list_init(set, destory)) == NULL) return NULL;

    set->match = match;

    return set;
}

int set_insert(Set *set, const void *data){
    if(set_is_member(set, data)) return -1;
    return list_ins_next(set, set->tail, data);
}

int set_remove(Set *set, void **data){
    ListNode *node = set->head, *prev= NULL;
    while(node && !(set->match(node->data, *data))){
        prev = node;
        node = node->next;
    }
    if(node == NULL) return -1;

    return list_rem_next(set, prev ,data);
}

int set_insert_trick(Set *set, void *data){
    if(set_insert(set, data) != 0){
        set_destory(set);
        return -1;
    }
    else return 0;
}

Set *set_union(Set *setu, const Set *set1, const Set *set2){
    // share the data, so not destory the data    
    if((setu = set_init(setu, set1->match, NULL)) == NULL) return NULL;

    ListNode *node = NULL;

    for(node = set1->head; node != NULL; node = node->next){        
        if(set_insert_trick(setu, node->data) != 0) return NULL;
    }

    for(node = set2->head; node != NULL; node = node->next){
        if(!set_is_member(setu, node->data)){
            if(set_insert_trick(setu, node->data) != 0) return NULL;
        }
    }

    return setu;
}

Set *set_intersection(Set *seti, const Set *set1, const Set *set2){
    if((seti = set_init(seti, set1->match, NULL)) == NULL) return NULL;

    int set1Larger = ((set1->size > set2->size) ? 1 : 0);

    for(ListNode *node = (!set1Larger ? set1->head : set2->head);
        node != NULL; node = node->next){
            if(set1Larger){
                if(set_is_member(set1, node->data)){
                    if(set_insert_trick(seti, node->data) != 0) return NULL;
                }
            }else{
                if(set_is_member(set2, node->data)){
                    if(set_insert_trick(seti, node->data) != 0) return NULL;
                }
            }
        }
    return seti;
}

Set *set_difference(Set *setd, const Set *set1, const Set *set2){
    if((setd = set_init(setd, set1->match, NULL)) == NULL) return NULL;

    ListNode *node = NULL;

    for(node = set1->head; node != NULL; node = node->next){
        if(!set_is_member(set2, node->data)){
            if(set_insert_trick(setd, node->data) != 0) return NULL;
        }
    }

    return setd;
}

int set_is_member(const Set *set, const void *data){
    for(ListNode *node = set->head; node != NULL; node = node->next)
        if(set->match(node->data, data)) return 1;
    return 0;
}

int set_is_subset(const Set *set1, const Set *set2){
    if(set2->size > set1->size) return 0;

    for(ListNode *node = set2->head; node != NULL; node = node->next)
        if(!set_is_member(set1, node->data)) return 0;
    return 1;
}

int set_is_equal(const Set *set1, const Set *set2){
    if(set1->size == set2->size){
        if(set_is_subset(set1, set2) == 1) return 1;
        else return 0;
    }else return 0;
}

