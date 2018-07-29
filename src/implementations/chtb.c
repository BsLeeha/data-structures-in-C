#include "../headers/chtb.h"
#include <stdlib.h>
#include <string.h>

CHTB *chtb_init(CHTB *chtb, int buckets, int (*h)(const void *key), 
              int (*match)(const void *key1, const void *key2),
              void (*destory)(void *data)){
    if(chtb == NULL) if((chtb = malloc(sizeof *chtb)) == NULL) return NULL;

    // allocate hash table
    if((chtb->table = malloc(buckets * sizeof *(chtb->table))) == NULL) return NULL; 

    // initialize buckets
    chtb->buckets = buckets;
    for(size_t i = 0; i < buckets; ++i) {
        List *temp = &(chtb->table)[i];
        temp = list_init(temp, destory);
    }

    chtb->size    = 0;
    chtb->h       = h;
    chtb->match   = match;
    chtb->destory = destory;

    return chtb;
}

int chtb_destory(CHTB *chtb){
    if(chtb == NULL) return -1;

    // destory each bucket
    for(size_t i = 0; i < chtb->buckets; ++i)
        list_destory(&chtb->table[i]);
    
    free(chtb->table);
    memset(chtb, 0, sizeof(CHTB));

    return 0;
}

int chtb_insert(CHTB *chtb, const void *data){
    if(chtb == NULL) return -1;
    if(chtb_lookup(chtb, (void **)&data) == 1) return -1;

    int bucket_id;

    bucket_id = chtb->h(data) % chtb->buckets;

    if(list_ins_next(&chtb->table[bucket_id], NULL, data) != 0) return -1;

    chtb->size++;
    return 0;
}

int chtb_remove(CHTB *chtb, void **data){
    if(chtb == NULL) return -1;

    ListNode *prev = NULL;
    int bucket_id;

    bucket_id = chtb->h(data) % chtb->buckets;

    for(ListNode *node = (&chtb->table[bucket_id])->head; node != NULL; node = node->next){
        if(chtb->match(node->data, *data)){
            if(list_rem_next(&chtb->table[bucket_id], prev, data) == 0) {
                (chtb->size)--;
                return 0;
            }
            else return -1; 
        }
        prev = node;
    }
}

int chtb_lookup(const CHTB *chtb, void **data){
    if(chtb == NULL) return -1;

    int bucket_id;

    bucket_id = chtb->h(*data) % chtb->buckets;
    
    for(ListNode *node = (&chtb->table[bucket_id])->head; node != NULL; node = node->next){
        if(chtb->match(node->data, *data)){
            *data = node->data;
            return 1;   // lookup success
        }
    }
    return 0;   // lookup fail, no such value
}   