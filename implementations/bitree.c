#include "../headers/bitree.h"
#include "../headers/list.h"
#include <stdlib.h>
#include <string.h>

BiTree *bitree_init(BiTree *bt, void (*destory_data)(void *data)){
    if(bt  == NULL) {
        if((bt = malloc(sizeof *bt)) == NULL) return NULL;
        bt->destory_tree = free;
    }else bt->destory_tree = NULL; 

    bt->root          = NULL;
    bt->size          = 0;
    bt->destory_data  = destory_data;

    return bt;
}

int bitree_destory(BiTree *bt){
    if(bt == NULL) return -1;       // bt doesn't initialize

    bitree_rem_left(bt, NULL);

    bt->size = 0;
    if(bt->destory_tree == NULL) memset(bt, 0, sizeof(BiTree));
    else bt->destory_tree(bt);

    return 0;
}

int bitree_ins_trick(BiTree *bt, BiTreeNode *node, const void *data, bool left){
    if(bt == NULL) return -1;
    BiTreeNode *new_node, **pos;

    if((new_node = malloc(sizeof *new_node)) == NULL) return -1;
    new_node->data  = (void *)data;
    new_node->left  = NULL;
    new_node->right = NULL;

    pos = ((node == NULL) ? &(bt->root) : (left ? &(node->left) : &(node->right)));

    if(*pos) return -1;
    else *pos = new_node;

    ++(bt->size);
    return 0;    
}

int bitree_rem_trick(BiTree *bt, BiTreeNode *node, bool left){
    if(bt == NULL) return -1;

    BiTreeNode **pos = NULL;
    pos = ((node == NULL) ? &(bt->root) : (left ? &(node->left) : &(node->right)));

    if(*pos == NULL) return -1;

    bitree_rem_trick(bt, *pos, 1);
    bitree_rem_trick(bt, *pos, 0);
    if(bt->destory_data) bt->destory_data((*pos)->data);
    free(*pos);
    
    *pos = NULL;

    --(bt->size);
    return 0;
}

// merge two trees and set the new node of data as the root node
int bitree_merge(BiTree *res, BiTree *left, BiTree *right, const void *data){
    BiTreeNode *new_node;

    res = bitree_init(res, left->destory_data);
    if((new_node = malloc(sizeof *new_node)) == NULL) return -1;
    new_node->data = (void *)data;

    left->root = (left ? left->root : NULL);
    right->root = (right ? right->root : NULL);

    new_node->left = left->root;
    new_node->right = right->root;

    res->root = new_node;
    res->size = left->size + right->size + 1;
    return 0;
}

void bitree_inOrderTraverse(const BiTreeNode *root, tree_iterator iterator){
    if(root){
        bitree_inOrderTraverse(root->left, iterator);
        iterator(root->data);
        bitree_inOrderTraverse(root->right, iterator);    
    }
}

int prefix(const BiTreeNode *root, List *list){
    if(!root) return -1;

    if(list_ins_next(list, list->tail, root->data) == -1) return -1;
    if(root->left)  if(prefix(root->left, list) == -1) return -1;
    if(root->right) if(prefix(root->right, list) == -1) return -1;

    return 0;
}

int infix(const BiTreeNode *root, List *list){
    if(!root) return -1;

    if(root->left)  if(infix(root->left, list) == -1) return -1;
    if(list_ins_next(list, list->tail, root->data) == -1) return -1;
    if(root->right) if(infix(root->right, list) == -1) return -1;

    return 0;
}

int postfix(const BiTreeNode *root, List *list){
    if(!root) return -1;

    if(root->left)  if(postfix(root->left, list) == -1) return -1;
    if(root->right) if(postfix(root->right, list) == -1) return -1;
    if(list_ins_next(list, list->tail, root->data) == -1) return -1;

    return 0;
}

