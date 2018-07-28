#pragma once

// BiTreeNode dynamically allocated and freed it in program
// BiTree and node data allocated and freed by user
typedef struct BiTreeNode_{
    void                *data;
    struct BiTreeNode_  *left;
    struct BiTreeNode_  *right;
}BiTreeNode;

typedef struct{
    BiTreeNode  *root;
    int          size;
    void         (*destory_tree)(void *tree);
    void         (*destory_data)(void *data); 
}BiTree;

typedef void (*tree_iterator)(const void *data);

typedef enum{false, true} bool;

/* public interface */
BiTree *bitree_init(BiTree *bt, void (*destory_data)(void *data));

int bitree_destory(BiTree *bt);

int bitree_ins_trick(BiTree *bt, BiTreeNode *node, const void *data, bool left);

#define bitree_ins_left(bt, node, data) (bitree_ins_trick((bt), (node), (data), true))

#define bitree_ins_right(bt, node, data) (bitree_ins_trick((bt), (node), (data), false))

int bitree_rem_trick(BiTree *bt, BiTreeNode *node, bool left);

#define bitree_rem_left(bt, node) (bitree_rem_trick((bt), (node), true))

#define bitree_rem_right(bt, node) (bitree_rem_trick((bt), (node), false))

// merge two trees and set the new node of data as the root node
int bitree_merge(BiTree *res, BiTree *left, BiTree *right, const void *data);

void bitree_inOrderTraverse(const BiTreeNode *root, tree_iterator iterator);

