//
//  CircleList.c
//  C
//
//  Created by K K on 2018/12/6.
//  Copyright © 2018 K K. All rights reserved.
//

#include "CircleList.h"
#include <stdlib.h>

CircleList *clist_init(void(*destory)(void *data)) {
    CircleList *list;
    if ((list = (CircleList *)malloc(sizeof(CircleList))) == NULL) {
        return NULL;
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->destory = destory;
    return list;
}


Node *clist_insert_next(CircleList *list, Node *node, const void *data) {
    if (list == NULL) {
        return NULL;
    }
    
    Node *new;
    if ((new = (Node *)malloc(sizeof(Node))) == NULL) {
        return NULL;
    }
    new->data = (void *)data;
    if (list->size == 0) {
        list->head = new;
        list->head->next = NULL;
        list->tail = new;
        list->tail->next = NULL;
    } else {
        if (node == NULL) {
            // 从链表头部插入
            new->next = list->head;
            list->head = new;
        } else {
            new->next = node->next; // 将原节点的下一个节点指向新节点的下一个节点，释放出node的下一个节点准备
            node->next = new;       // node节点的下一个节点指向新节点，形成闭环
            if (new->next == NULL) {
                // 如果node之前的下一个节点为null，即只有一个节点元素时
                new->next = list->head;
            }
            
            if (node == list->tail) {
                // 如果node是尾节点，跟新尾节点
                list->tail = node;
            }
        }
    }
    
    list->size++;
    return new;
}




int clist_remove_next(CircleList *list, Node *node, void **data) {
    // 排除链表为空
    if (list == NULL) {
        return 0;
    }
    
    // 排除链表没有元素
    if (list->size == 0) {
        return 0;
    }
    
    // 如果元素只有一个
    Node *temp;
    if(list->size == 1) {
        list->tail = NULL;
        temp = list->head;
        list->head = NULL;
    } else {
        if (node == NULL) {
            // 删除头部元素
            temp = list->head; // 取出头部元素
            list->head = list->head->next; // 从链表的头部元素指向下一个元素，即链表中删除头部元素的存在
            list->tail->next = list->head; // 将尾部元素的下一个元素指向新的元素
        } else {
            temp = node->next; // 取出node的下一个元素
            node->next = temp->next; // 将node的下一个元素指向删除的下一个元素，即让要删除的元素移除链表
        }
        
        if (list->size == 2) {
            // 删除后只有一个元素了，让他们的下一个元素为null
            list->head->next = NULL;
        }
    }
    
    *data = temp->data;
    free(temp);
    list->size--;
    return 1;
}


void displayCircleList(CircleList *list) {
    if (list == NULL) {
        // 链表为空
        printf("当前链表为空\n");
        return;
    }
    
    if (list->size == 0) {
        printf("当前链表的个数为0\n");
        return;
    }
    
    int size = list->size;
    Node *temp = list->head;
    printf("当前链表的个数为%d\n",size);
    while (size>0) {
        printf("%d\n",*(int *)(temp->data));
        temp = temp->next;
        size--;
    }
    printf("打印结束\n");
}
