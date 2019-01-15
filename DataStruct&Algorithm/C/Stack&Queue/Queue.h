//
//  Queue.h
//  C
//
//  Created by K K on 2018/12/9.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include "../List/List.h"

typedef SingleList Queue;

#define quene_init(destory) init_list(destory)
#define queue_destory(list, destory) list_destory(list, destory)


/**
 入队列

 @param queue 队列
 @param data 要入队列的数据
 @return 成功加入的节点
 */
Node *queue_in(Queue *queue, const void *data);


/**
 出队列

 @param queue 队列
 @param data 出队列的节点的数据
 @return 是否成功
 */
int queue_out(Queue *queue, void **data);


void displayQueue(Queue *queue);

#endif /* Queue_h */
