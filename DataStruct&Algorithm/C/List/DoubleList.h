//
//  DoubleList.h
//  C
//
//  Created by K K on 2018/12/6.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef DoubleList_h
#define DoubleList_h

#include <stdio.h>

typedef struct NodeD {
    void *data;
    struct NodeD* next;
    struct NodeD* pre;
} NodeD;


typedef struct DoubleList {
    
    int size;
    NodeD *head;
    NodeD *tail;
    void (*destory) (void *data); // 数据的析构函数
    
} DoubleList;

#define dlist_size(list) (list->size)
#define dlist_head(list) (list->head)
#define dlist_tail(list) (list->tail)
#define dlist_next(node) (node->next)
#define dlist_pre(node) (node->pre)

/**
 构造函数

 @return 构造后的链表
 */
DoubleList *dlist_init(void);



/**
 析构函数

 @param list 链表
 @param destory 析构元素函数
 */
void dlist_destory(DoubleList *list, void(*destory)(void *data));


/**
 插入元素

 @param list 链表
 @param node 对应节点，如果此节点为null，则从尾部插入数据
 @param data 插入的数据
 @param next 插入的位置，1在后面插入，其他在前面插入
 @return 插入的节点
 */
NodeD* dlist_insert_next(DoubleList *list, NodeD *node, const void *data, int next);



/**
 删除元素

 @param list 链表
 @param node 对应节点，如果此节点为nil，则从头部开始删除一个
 @param data 被删除的节点的数据
 @param next 被删除的位置，1删除后面的，其他删除前面的
 @return 是否删除成功
 */
int dlist_remove_next(DoubleList *list, NodeD *node, void **data, int next);



void displayDlist(DoubleList* list);
#endif /* DoubleList_h */
