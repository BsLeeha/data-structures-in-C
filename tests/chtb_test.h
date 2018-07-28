#pragma once

#include <stdio.h>
#include "../headers/chtb.h"
#include "../headers/print.h"
#include "set_test.h"

int hash(const void *key){
    return *(int *)key;
}

void chtb_test(){
    printf("chtb test:\n");

    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr)/sizeof(arr[0]);
    CHTB *chtb = NULL;
    chtb = chtb_init(chtb, 5, hash, match, NULL);
    for(size_t i = 0; i < 5; ++i) chtb_insert(chtb, &arr[i]);
    for(size_t i = 0; i < 5; ++i){
        int j = i;
        int *p = &j;
        if((chtb_lookup(chtb, (void **)&p) == 1))
        printf("%d ", *(int *)p);
    }    

    printf("\n\n");
}