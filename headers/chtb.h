#ifndef CHTB_H
#define CHTB_H

#include "list.h"

/* structure for chained hash tables */
typedef struct CHTB_{
    // hash table(List arrays)
    List *table;    
    // # of buckets(table size)
    int  buckets;           
    // # total elems
    int  size;       
    // hash function(key to bucket_id)
    int  (*h)(const void *key);
    // match function
    int  (*match)(const void *key1, const void *key2);
    // destory function
    void (*destory)(void *data);
}CHTB;

/* public interfaces */
// initialize the chained hash table, allocate the chtb if necessary
CHTB *chtb_init(CHTB *chtb, int buckets, int (*h)(const void *key), 
              int (*match)(const void *key1, const void *key2),
              void (*destory)(void *data));

// destory the chained hash table
int chtb_destory(CHTB *chtb);

// insert an elem into the specified bucket
int chtb_insert(CHTB *chtb, const void *data);

// use list_rem_next to remve the elem in the specified bucket
int chtb_remove(CHTB *chtb, void **data);

// deteremine whether an elem matches data int 
int chtb_lookup(const CHTB *chtb, void **data);

#define chtb_size(chtb) ((chtb)->size)

#endif // CHTB_H