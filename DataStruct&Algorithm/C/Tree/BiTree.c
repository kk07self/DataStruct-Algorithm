//
//  BitTree.c
//  C
//
//  Created by K K on 2018/12/13.
//  Copyright © 2018 K K. All rights reserved.
//

#include "BiTree.h"
#include <stdlib.h>

BiTree *bitree_init(void(*destory)(void *data), int(*compare) (const void *data1, const void *data2)) {
    
    // 创建二叉树
    BiTree *bitree;
    if ((bitree = (BiTree *)malloc(sizeof(BiTree))) == NULL) {
        return NULL;
    }
    bitree->size = 0;
    bitree->root = NULL;
    bitree->compare = compare;
    bitree->destory = destory;
    return bitree;
}


void destory(BiTree *bitree) {
    if (bitree == NULL) {
        return;
    }
    bitree_remove_left(bitree, NULL);
    bitree->root = NULL;
    free(bitree);
}


BiTreeNode *bitree_insert_left(BiTree *bitree, BiTreeNode *node, const void *data) {
    if (bitree == NULL) {
        return NULL;
    }
    
    if (bitree->size > 0 && node == NULL) {
        return  NULL;
    }
    
    if (node != NULL && node->left != NULL) {
        return NULL;
    }
    
    BiTreeNode *new;
    if ((new = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL) {
        return NULL;
    }
    new->data = (void *)data;
    new->left = NULL;
    new->right = NULL;
    
    if (node == NULL) {
        bitree->root = new;
    } else {
        node->left = new;
    }
    bitree->size++;
    return new;
}


BiTreeNode *bitree_insert_right(BiTree *bitree, BiTreeNode *node, const void *data) {
    if (bitree == NULL) {
        return NULL;
    }
    
    if (bitree->size > 0 && node == NULL) {
        return  NULL;
    }
    
    if (node->right != NULL) {
        return NULL;
    }
    
    BiTreeNode *new;
    if ((new = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL) {
        return NULL;
    }
    new->data = (void *)data;
    new->left = NULL;
    new->right = NULL;
    
    if (node == NULL) {
        bitree->root = new;
    } else {
        node->right = new;
    }
    bitree->size++;
    return new;
}


void bitree_remove_left(BiTree *bitree, BiTreeNode *node) {
    if (bitree == NULL || bitree->size == 0) {
        return;
    }
    
    BiTreeNode **position;
    if (node == NULL) {
        position = &(bitree->root);
    } else {
        position = &(node->left);
    }
    
    if (*position != NULL) {
        bitree_remove_left(bitree, *position);
        bitree_remove_right(bitree, *position);
        if (bitree->destory != NULL) {
            bitree->destory((*position)->data);
        }
        (*position)->left = NULL;
        (*position)->right = NULL;
        free(*position);
        bitree->size--;
        position = NULL;
    }
}

void bitree_remove_right(BiTree *bitree, BiTreeNode *node) {
    if (bitree == NULL || bitree->size == 0) {
        return;
    }
    
    BiTreeNode **position;
    if (node == NULL) {
        position = &(bitree->root);
    } else {
        position = &(node->right);
    }
    
    if (*position != NULL) {
        bitree_remove_left(bitree, *position);
        bitree_remove_right(bitree, *position);
        if (bitree->destory != NULL) {
            bitree->destory((*position)->data);
        }
        (*position)->left = NULL;
        (*position)->right = NULL;
        free(*position);
        bitree->size--;
        position = NULL;
    }
}


BiTree *bitree_merge(BiTree *left, BiTree *right, const void *data) {
    
    BiTree *bitree;
    if ((bitree = bitree_init(left->destory, left->compare)) == NULL) {
        return NULL;
    }
    
    BiTreeNode *node;
    if ((node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL) {
        return NULL;
    }
    node->data = (void *)data;
    node->left = left->root;
    node->right = left->root;
    bitree->root = node;
    
    left->root = NULL;
    free(left);
    right->root = NULL;
    free(right);
    return bitree;
}


void displayTreeRight(BiTree *tree, BiTreeNode *node);
void displayTreeLeft(BiTree *tree, BiTreeNode *node) {
    BiTreeNode *postion;
    if (tree == NULL) {
        printf("这个数是NULL\n");
        return;
    }
    if (node == NULL) {
        return;
    }
    
    if (node == NULL) {
        postion = tree->root;
    } else {
        postion = node->left;
    }
    if (postion != NULL) {
        printf("左节点-----%d\n",*(int *)postion->data);
    }
    
    displayTreeLeft(tree, postion);
    displayTreeRight(tree, postion);
}

void displayTreeRight(BiTree *tree, BiTreeNode *node) {
    BiTreeNode *postion;
    if (tree == NULL) {
        printf("这个数是NULL\n");
        return;
    }
    if (node == NULL) {
        return;
    }

    if (node == NULL) {
        postion = tree->root;
    } else {
        postion = node->right;
    }
    if (postion != NULL) {
        printf("左节点-----%d\n",*(int *)postion->data);
    }
    displayTreeLeft(tree, postion);
    displayTreeRight(tree, postion);
}



void displayTree(BiTree *tree) {
    if (tree == NULL) {
        printf("这个树是NULL\n");
        return;
    }
    if (tree->size == 0) {
        printf("这个树的个数是0\n");
        return;
    }
    
    printf("这个树的个数是%d\n", tree->size);
    printf("根节点-----%d\n",*(int *)tree->root->data);
    displayTreeLeft(tree, tree->root);
    displayTreeRight(tree, tree->root);
}

