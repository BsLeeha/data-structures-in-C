#pragma once

#include "list.h"

// implement sets as lists
typedef ListNode SetNode;

typedef List Set;

// public interfaces
Set *set_init(Set *set, int (*match)(const void *key1, const void *key2), 
                       void (*destory)(void *data));

#define set_destory list_destory

int set_insert(Set *set, const void *data);

int set_remove(Set *set, void *data, void **old_data);

Set *set_union(Set *setu, const Set *set1, const Set *set2);

Set *set_intersection(Set *seti, const Set *set1, const Set *set2);

Set *set_difference(Set *setd, const Set *set1, const Set *set2);

int set_is_member(const Set *set, const void *data);

int set_is_subset(const Set *set1, const Set *set2);

int set_is_equal(const Set *set1, const Set *set2);

#define set_for_each list_for_each

#define set_size list_size