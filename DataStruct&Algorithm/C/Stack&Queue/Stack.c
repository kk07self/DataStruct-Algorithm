//
//  Stack.c
//  C
//
//  Created by K K on 2018/12/9.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdlib.h>
#include "Stack.h"


Node *stack_push(Stack *stack, const void *data) {
    return list_insert_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data) {
    return list_remove_next(stack, NULL, data);
}

void displayStack(Stack *stack) {
    if (stack == NULL) {
        printf("此栈未初始化\n");
        return;
    }
    
    if (stack->size == 0) {
        printf("此栈目前节点数为0\n");
        return;
    }
    
    printf("此栈目前节点个数为%d\n",stack->size);
    Node *temp = stack->head;
    while (temp != NULL) {
        printf("%d\n",*(int *)(temp->data));
        temp = temp->next;
    }
    printf("打印结束\n");
}
