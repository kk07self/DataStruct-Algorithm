//
//  Queue.c
//  C
//
//  Created by K K on 2018/12/9.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdlib.h>
#include "Queue.h"


Node *queue_in(Queue *queue, const void *data) {
    if (queue == NULL) {
        return NULL;
    }
    Node *node;
    if ((node = (Node *)malloc(sizeof(Node))) == NULL) {
        return NULL;
    }
    node->data = (void *)data;
    if (queue->size == 0) {
        queue->head = node;
        queue->tail = node;
        node->next = NULL;
    } else {
        queue->tail->next = node; // 链接到队列中
        queue->tail = node; // 替换掉尾节点
        node->next = NULL;
    }
    queue->size++;
    return node;
}


int queue_out(Queue *queue, void **data) {
    return list_remove_next(queue, NULL, data);
}

void displayQueue(Queue *queue) {
    if (queue == NULL) {
        printf("此队列未初始化\n");
        return;
    }
    
    if (queue->size == 0) {
        printf("此队列目前节点数为0\n");
        return;
    }
    
    printf("此队列目前节点个数为%d\n",queue->size);
    Node *temp = queue->head;
    while (temp != NULL) {
        printf("%d\n",*(int *)(temp->data));
        temp = temp->next;
    }
    printf("打印结束\n");
}
