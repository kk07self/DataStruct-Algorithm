//
//  List.h
//  C
//
//  Created by K K on 2018/12/4.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef List_h
#define List_h

#include <stdio.h>

#pragma 单向列表
/**
 单向列表元素
 */
typedef struct Node {
    void *data;                         // 数据内容
    struct Node *next;     // 下一个元素
} Node;


/**
 单向列表
 */
typedef struct SingleList {
    Node *head; // 列表头
    Node *tail; // 列表尾
    int size; // 列表个数
    void (*destory) (void *data); // 数据的析构函数
} SingleList;


// 方法区域

/**
 初始化链表

 @return 初始化后的链表
 */
SingleList* init_list(void(*destory)(void *data));


/**
 析构函数：析构整个链表

 @param list 要析构的链表
 @param destory 单个元素中数据的析构函数，如果为null就调用链表里面保存的析构函数
 */
void list_destory(SingleList *list, void(*destory)(void *data));


/**
 插入元素，在指定的元素后面

 @param list 链表
 @param element 指定的元素
 @param data 要插入的数据
 @return 是否插入成功，失败-1，成功是0
 */
Node* list_insert_next(SingleList *list, Node *element, const void *data);


/**
 删除元素

 @param list 链表
 @param element 指定的元素
 @param data 删除元素的数据
 @return 是否删除成功，-1删除
 */
int list_remove_next(SingleList *list, Node *element, void **data);

#define list_size(list) (list->size)
#define list_head(list) (list->head)
#define list_tail(list) (list->tail)
#define list_is_head(list, element) ((list->head == element) ? 1 : 0)
#define list_is_tail(element) ((element->next)==NULL ? 1 : 0)


/**
 链表反转

 @param list 链表
 */
void list_reverse(SingleList *list);



/**
 有序链表合并

 @param one 有序链表1
 @param two 有序链表2
 @param match 元素大小比较
 @return 合并后的新链表
 */
SingleList* list_merge(SingleList *one, SingleList *two, int(*match)(const void* data1, const void* data2));


/**
 链表中删除倒数第index个节点

 @param list 链表
 @param index 倒数index
 @param data 被删除的元素中的数据
 @return 是否成功，-1未成功
 */
int list_remove_rindex_element(SingleList *list, int index, void **data);



/**
 链表中的中间节点

 @param list 链表
 @return 中间节点
 */
Node *list_midle_element(SingleList *list);


// 链表中环的检测

void displayElements(SingleList* list);

#endif /* List_h */
