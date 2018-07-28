#pragma once

#include "../headers/bitree.h"
#include "../headers/print.h"
#include <stdio.h>

void bitree_test(){
    printf("bitree test:\n");

    int arr[] = {1, 2, 4, 3, 5};
    size_t len = sizeof(arr)/sizeof(arr[0]);    
    BiTree bt;
    int a = 10;
    bitree_init(&bt, NULL);
    bitree_ins_left(&bt, NULL, &a);
    BiTreeNode *node = bt.root;
    for(size_t i = 0; i < len; ++i) {
        bitree_ins_left(&bt, node, &arr[i]);
        node = node->left;
    }
    bitree_inOrderTraverse(bt.root, int_print);
    printf("\n");
    bitree_rem_left(&bt, bt.root);
    bitree_inOrderTraverse(bt.root, int_print);
    printf("\n");
    bitree_destory(&bt);

    printf("\n\n");
}