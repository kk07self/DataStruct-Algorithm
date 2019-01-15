//
//  List.c
//  C
//
//  Created by K K on 2018/12/4.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdlib.h>
#include "List.h"


SingleList* init_list(void(*destory)(void *data)) {
    SingleList *list;
    if ((list = (SingleList*)malloc(sizeof(SingleList))) == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destory = destory;
    return list;
}

Node* list_insert_next (SingleList *list, Node *element, const void *data) {
    // 过滤list为null
    if (list == NULL) {
        return NULL;
    }
    
    Node *new;
    if ((new = (Node*)malloc(sizeof(Node))) == NULL) {
        return NULL;
    }
    new->data = (void *)data;
    new->next = NULL;
    
    // 当前列表为空
    if (list->head == NULL ) {
        list->head = new;
        list->tail = new;
        list->size++;
        return new;
    }
    
    // 正常插入
    if (element != NULL) {
        new->next = element->next;
        element->next = new;
    } else {
        // 插入到最前面
        new->next = list->head;
        list->head = new;
    }
    
    // 如果插入到尾部
    if (element == list->tail) {
        list->tail = new;
    }
    list->size++;
    return new;
}



int list_remove_next(SingleList *list, Node *element, void **data) {
    if (list == NULL || list_size(list) == 0) {
        return -1;
    }
    
    Node *old_element;
    if (element == NULL) {
        // element没有就删除头部
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        if (list_size(list) == 1) {
            // 只有一个的情况下清空尾部
            list->tail = NULL;
        }
    } else {
        // 正常删除
        if (element->next == NULL) {
            return -1;
        }
        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;
        if (element->next == NULL) {
            list->tail = element;
        }
    }
    free(old_element);
    list->size--;
    return 0;
}


void list_destory(SingleList *list, void(*destory)(void *data)) {
    // 过滤列表为空
    if (list == NULL) {
        return;
    }
    
    // 过滤元素为空
    if (list->size == 0) {
        free(list);
        return;
    }
    void *data;
    while (list->size > 0) {
        if (list_remove_next(list, NULL, &data) == 0 && data != NULL) {
            if (destory != NULL) {
                destory(data);
            } else if (list->destory != NULL) {
                list->destory(data);
            }
        }
    }
}

void list_reverse(SingleList *list) {
    
    // 空或者为1的时候不进行处理
    if (list == NULL || list->size <= 1) {
        return;
    }
    
    // 拿出next，让当前的元素断开然后关联到反转的链表中
    Node *next = list->head->next;
    // 拿出next的next
    Node *nextNext = next->next;
    
    // 头部拿出插入到尾部
    list->head->next = NULL;
    list->tail = list->head;
    
    // 操作后面的部分
    while (nextNext != NULL) { // 判断到尾部了
        // 将next插入到头部
        next->next = list->head;
        list->head = next;
        
        // 将next的next给到要插入的next进行循环操作
        next = nextNext;
        nextNext = nextNext->next;
    }
    // 当nextNext为NULL时，next是原来的tail尾部元素，这时需要将其插入到头部
    next->next = list->head;
    list->head = next;
}


void displayElements(SingleList* list) {
    if (list == NULL || list->head == NULL) {
        printf("list is NULL\n");
        return;
    }
    Node *element = list->head;
    printf("elements count of list : %d\n", list->size);
//    printf("head of list : %d\n", *((int*)(list->head)));
    while (element != NULL) {
        printf("%d\n", *(int*)(element->data));
        element = element->next;
    }
//    printf("tail of list : %d\n", *((int*)(list->tail)));
}



SingleList* list_merge(SingleList *one, SingleList *two, int(*match)(const void* data1, const void* data2)) {
    
    SingleList *list = init_list(one->destory);
    if (list == NULL) {
        return NULL;
    }
    list->size = one->size + two->size;
    // 任何一方为空的情况下
    if (one->size == 0) {
        list->head = two->head;
        list->size = two->size;
        list->tail = two->tail;
        return list;
    } else if (two->size == 0) {
        list->head = one->head;
        list->size = one->size;
        list->tail = one->tail;
        return list;
    }
    
    Node *oneN = one->head;
    Node *twoN = two->head;
    Node *new;
    if (match(oneN->data, twoN->data) > 0) {
        new = twoN;
        twoN = twoN->next;
    } else {
        new = oneN;
        oneN = oneN->next;
    }
    list->head = new;
    
    while (oneN != NULL && twoN != NULL) {
        if (match(oneN->data, twoN->data) > 0) {
            new->next = twoN;
            twoN = twoN->next;
        } else {
            new->next = oneN;
            oneN = oneN->next;
        }
        new = new->next;
    }
    if (oneN == NULL) {
        new->next = twoN;
        list->tail = two->tail;
    } else {
        new->next = oneN;
        list->tail = one->tail;
    }
    return list;
}

int list_remove_rindex_element(SingleList *list, int index, void **data) {

    // 移除倒数第index就是移除正数第（list->size - index）
    int preI = list->size - index;
    if (preI < 0) {
        return -1;
    }
    
    int i = 1;
    Node *pre = NULL;
    Node *temp = list->head;
    while (i <= preI) {
        pre = temp;
        temp = temp->next;
        i++;
    }
    *data = temp->data;
    if (pre == NULL) {
        // 删除的是第一个
        list->head = temp->next;
    } else {
        // 删除的不是第一个元素
        pre->next = temp->next;
        if (pre->next == NULL) {
            // 删除最后一个
            list->tail = pre;
        }
    }
    free(temp);
    list->size--;
    return 0;
}

Node *list_midle_element(SingleList *list) {
    if (list->size == 0) {
        return NULL;
    }
    
    if (list->size < 2) {
        return list->head;
    }
    
    int mid = list->size*0.5;
    if (list->size%2 == 0) {
        mid--;
    }
    
    Node *temp = list->head;
    
    int i = 1;
    while (i <= mid) {
        temp = temp->next;
        i++;
    }
    return  temp;
}
