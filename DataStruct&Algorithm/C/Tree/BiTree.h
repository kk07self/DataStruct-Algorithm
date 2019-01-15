//
//  BitTree.h
//  C
//
//  Created by K K on 2018/12/13.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef BiTree_h
#define BiTree_h

#include <stdio.h>


/**
 二叉树节点
 */
typedef struct BiTreeNode {
    
    void *data;
    struct BiTreeNode *left;  // 左侧子节点
    struct BiTreeNode *right; // 右侧子节点
    
} BiTreeNode;


typedef struct BiTree {
    
    BiTreeNode *root; // 根节点
    void (*destory) (void *data);
    int  (*compare) (const void *data1, const void *data2);
    int size;
    
} BiTree;



/**
 初始化二叉树

 @param destory 析构数据函数
 @param compare 比较两个数据函数
 @return 初始化后的二叉树
 */
BiTree *bitree_init(void(*destory)(void *data), int(*compare) (const void *data1, const void *data2));


/**
 析构二叉树

 @param bitree 二叉树
 */
void destory(BiTree *bitree);


/**
 插入左侧子节点

 @param bitree 二叉树
 @param node 对应节点
 @param data 要插入的数据
 @return 插入后的节点，为null即插入失败
 */
BiTreeNode *bitree_insert_left(BiTree *bitree, BiTreeNode *node, const void *data);

/**
 插入右侧侧子节点
 
 @param bitree 二叉树
 @param node 对应节点
 @param data 要插入的数据
 @return 插入后的节点，为null即插入失败
 */
BiTreeNode *bitree_insert_right(BiTree *bitree, BiTreeNode *node, const void *data);


/**
 删除某个节点的左侧子树

 @param bitree 二叉树
 @param node 对应节点
 */
void bitree_remove_left(BiTree *bitree, BiTreeNode *node);


/**
 删除某个节点的右侧子树
 
 @param bitree 二叉树
 @param node 对应节点
 */

void bitree_remove_right(BiTree *bitree, BiTreeNode *node);


/**
 合并两个子二叉树

 @param left 左侧二叉树
 @param right 右侧二叉树
 @param data 节点数据
 @return 合并后的二叉树
 */
BiTree *bitree_merge(BiTree *left, BiTree *right, const void *data);

#define bitree_size(bitree) (bitree->size)
#define bitree_root(bitree) (bitree->root)
#define bitree_is_eob(node) (node == NULL)
#define bitree_is_leaf(node) ((node)->left==NULL && (node)->right==NULL)
#define bitree_data(node) (node->data)
#define bitree_left(node) (node->left)
#define bitree_right(node) (node->right)


void displayTree(BiTree *tree);

#endif /* BitTree_h */
