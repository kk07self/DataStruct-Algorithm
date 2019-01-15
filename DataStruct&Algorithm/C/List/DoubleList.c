//
//  DoubleList.c
//  C
//
//  Created by K K on 2018/12/6.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdlib.h>
#include "DoubleList.h"

DoubleList *dlist_init(void) {
    DoubleList *list;
    if ((list = (DoubleList *)malloc(sizeof(DoubleList))) == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}


void dlist_destory(DoubleList *list, void(*destory)(void *data)) {
    
    if (list == NULL) {
        return;
    }
    if (list->size == 0) {
        free(list);
        return;
    }
    
    void *data;
    while (list->size > 0) {
        dlist_remove_next(list, NULL, &data, 0);
        if (destory != NULL) {
            destory(data);
        }
    }
}


NodeD* dlist_insert_next(DoubleList *list, NodeD *node, const void *data, int next) {
    
    // 链表为空时
    if (list == NULL || data == NULL) {
        return NULL;
    }
    
    NodeD *new;
    // 节点分配内存
    if ((new = (NodeD *)malloc(sizeof(NodeD))) == NULL) {
        return NULL;
    }
    new->data = (void *)data;
    new->next = NULL;
    new->pre = NULL;
    if (list->size == 0) {
        list->head = new;
        list->tail = new;
    } else {
        // 节点为NULL，加在最前面
        if (node == NULL) {
            new->next = list->head;
            list->head->pre = new;
            list->head = new;
        } else {
            // 插在后面
            if (next == 1) {
                if (node->next != NULL) {
                    node->next->pre = new;
                } else {
                    list->tail = new;
                }

                new->next = node->next;
                node->next = new;
                new->pre = node;
                
            } else {
                // 插在前面
                if (node->pre != NULL) {
                    node->pre->next = new;
                } else {
                    list->head = new;
                }
                new->next = node;
                new->pre = node->pre;
                node->pre = new;
                
            }
        }
    }
    list->size++;
    return new;
}


int dlist_remove_next(DoubleList *list, NodeD *node, void **data, int next) {
    
    if (list == NULL || list->size == 0) {
        return 0;
    }
    
    // 对应节点没有的话，删除头部的
    NodeD *temp;
    if (node == NULL) {
        temp = list->head;
        list->head = temp->next;
        list->head->pre = NULL;
    } else {
        if (next == 1) {
            // 删除后面的
            if (node == list->tail) {
                return 1;
            }
            temp = node->next;
            node->next = temp->next;
            // 要删除的是否是tail
            if (temp->next != NULL) {
                temp->next->pre = node;
            } else {
                list->tail = node;
            }
            
        } else {
            // 删除前面的
            if (node == list->head) {
                return 1;
            }
            temp = node->pre;
            // 要删除的是否是head
            if (temp->pre != NULL) {
                temp->pre->next = node;
            } else {
                list->head = node;
            }
            node->pre = temp->pre;
        }
    }
    
    *data = temp->data;
    if (list->destory != NULL) {
        list->destory(temp->data);
    }
    free(temp);
    list->size--;
    return 1;
    
}



void displayDlist(DoubleList* list) {
    if (list == NULL) {
        printf("list is null\n");
    }
    
    printf("Node are %d of list\n", list->size);
    
    printf("正序打印------------\n");
    NodeD *temp = list->head;
    while (temp != NULL) {
        printf("%d\n",*(int*)(temp->data));
        temp = temp->next;
    }
    
    printf("倒序打印------------\n");
    NodeD *temp2 = list->tail;
    while (temp2 != NULL) {
        printf("%d\n",*(int*)(temp2->data));
        temp2 = temp2->pre;
    }
}
