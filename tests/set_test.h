#pragma once

#include <stdio.h>
#include "../headers/set.h"
#include "../headers/print.h"

int match(const void *key1, const void *key2){
    return (*(int *)key1 == *(int *)key2);
}

void set_test(){
    printf("set:\n");

    Set *set1 = NULL, *set2 = NULL, *setu = NULL, *seti = NULL, *setd = NULL;
    set1 = set_init(set1, match, NULL);
    set2 = set_init(set2, match, NULL);
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {3, 4, 5, 6, 7};
    for(size_t i = 0; i < 5; ++i) set_insert(set1, &arr1[i]);
    for(size_t i = 0; i < 5; ++i) set_insert(set2, &arr2[i]);
    setu = set_union(setu, set1, set2);
    seti = set_intersection(seti, set1, set2);
    setd = set_difference(setd, set1, set2);
    set_for_each(set1, int_print);
    set_for_each(set2, int_print);
    set_for_each(setu, int_print);
    set_for_each(seti, int_print);
    set_for_each(setd, int_print);    

    printf("\n");

}