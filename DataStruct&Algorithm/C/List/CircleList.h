//
//  CircleList.h
//  C
//
//  Created by K K on 2018/12/6.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef CircleList_h
#define CircleList_h

#include <stdio.h>
#include "List.h"

/**
 循环列表
 */
typedef struct CircleList {
    Node *head; // 链表头
    Node *tail; // 链表尾
    int size; // 列表个数
    void (*destory) (void *data); // 数据的析构函数
} CircleList;


/**
 构造函数
 
 @param destory 节点内的数据进行析构的函数
 @return 构造后的链表
 */
CircleList *clist_init(void(*destory)(void *data));


/**
 析构函数

 @param list 要析构的链表
 */
void clist_destory(CircleList *list);

/**
 向链表中插入元素

 @param list 链表
 @param node 对应节点，如果node为null，默认从尾部插入一个
 @param data 要插入的数据
 @return 插入后的节点
 */
Node *clist_insert_next(CircleList *list, Node *node, const void *data);


/**
 从链表中删除元素

 @param list 链表
 @param node 对应的节点，如果node为null，默认从头部删除一个
 @param data 删除节点对应的数据
 @return 是否删除成功，1成功，否则失败
 */
int clist_remove_next(CircleList *list, Node *node, void **data);



void displayCircleList(CircleList *list);
#endif /* CircleList_h */
