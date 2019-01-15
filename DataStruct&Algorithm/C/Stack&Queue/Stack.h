//
//  Stack.h
//  C
//
//  Created by K K on 2018/12/9.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <stdio.h>
#include "../List/List.h"

typedef SingleList Stack;

#define stack_init(destory) init_list(destory)
#define stack_destory list_destory


/**
 压栈

 @param data 要压入的数据
 @return 压入的节点
 */
Node *stack_push(Stack *stack, const void *data);

int stack_pop(Stack *stack, void **data);


void displayStack(Stack *stack);

#endif /* Stack_h */
