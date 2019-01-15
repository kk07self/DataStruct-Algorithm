//
//  main.c
//  C
//
//  Created by K K on 2018/12/5.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdlib.h>
#include "List/List.h"
#include "List/DoubleList.h"
#include "List/CircleList.h"
#include "Stack&Queue/Stack.h"
#include "Stack&Queue/Queue.h"

#include "Sort/testSort.h"
#include "Tree/BiTree.h"


// 函数声明S
void testList(void);

void testListUnite(void);

void testDoubleList(void);
void testCircleList(void);

void testStack(void);
void testQueue(void);

BiTree* testBiTree(void);

int main(int argc, const char * argv[]) {
    // insert code here...
//    testList();
//    testDoubleList();
//    testCircleList();
//    testStack();
//    testQueue();
//    testSort();
    BiTree *bitree = testBiTree();
    destory(bitree);
    return 0;
}

int match(const void *a, const void *b) {
    return *((int *)a) > *((int *)b) ? 1 : -1;
}


BiTree* testBiTree(void) {
    
    BiTree *bitree = bitree_init(NULL, NULL);
    displayTree(bitree);
    int a = 10;
    BiTreeNode *node1 = bitree_insert_left(bitree, NULL, &a);
    int b = 20;
    BiTreeNode *node2 = bitree_insert_left(bitree, node1, &b);
    BiTreeNode *node3 = bitree_insert_right(bitree, node1, &b);
    displayTree(bitree);
    
    BiTreeNode *node4 = bitree_insert_left(bitree, node2, &b);
    BiTreeNode *node5 = bitree_insert_right(bitree, node2, &b);
    displayTree(bitree);
    bitree_remove_left(bitree, NULL);
    displayTree(bitree);
    return bitree;
}

// ------------------------------------队列----------------------------------------
void testQueue(void) {
    Queue *queue = quene_init(NULL);
    displayQueue(queue);
    int a = 10;
    Node *node1 = queue_in(queue, &a);
    int b = 20;
    Node *node2 = queue_in(queue, &b);
    int c = 30;
    Node *node3 = queue_in(queue, &c);
    int d = 40;
    Node *node4 = queue_in(queue, &d);
    int e = 50;
    Node *node5 = queue_in(queue, &e);
    displayQueue(queue);
    
    void *data;
    queue_out(queue, &data);
    displayQueue(queue);
    printf("%d\n",*(int *)data);
    queue_out(queue, &data);
    displayQueue(queue);
    printf("%d\n",*(int *)data);
    queue_out(queue, &data);
    displayQueue(queue);
    printf("%d\n",*(int *)data);
    queue_out(queue, &data);
    displayQueue(queue);
    printf("%d\n",*(int *)data);
}


// ------------------------------------栈----------------------------------------
void testStack() {
    Stack *stack;
    stack = stack_init(NULL);
    displayStack(stack);
    
    int a = 10;
    stack_push(stack, &a);
    displayStack(stack);
    
    int b = 20;
    stack_push(stack, &b);
    displayStack(stack);
    
    int c = 30;
    stack_push(stack, &c);
    displayStack(stack);
    
    void *data;
    stack_pop(stack, &data);
    displayStack(stack);
    printf("%d\n",*(int *)data);
}


// ------------------------------------循环链表----------------------------------------
void testCircleList() {
    CircleList *list;
    list = clist_init(NULL);
    displayCircleList(list);
    int a = 10;
    Node *node1 = clist_insert_next(list, NULL, &a);
    displayCircleList(list);
    
    int b = 30;
    Node *node2 = clist_insert_next(list, node1, &b);
    displayCircleList(list);
    printf("%d\n",*(int *)(node2->next->data));
    
    int c = 20;
    Node *node3 = clist_insert_next(list, node1, &c);
    displayCircleList(list);
    printf("%d\n",*(int *)(node3->next->data));
    
    int d = 40;
    Node *node4 = clist_insert_next(list, node2, &d);
    displayCircleList(list);
    printf("%d\n",*(int *)(node4->next->data));
    
    void *data;
    clist_remove_next(list, NULL, &data);
    displayCircleList(list);
    printf("%d\n", *(int *)(data));
    
    clist_remove_next(list, node2, &data);
    displayCircleList(list);
    printf("%d\n", *(int *)(data));
}


// ------------------------------------双向链表----------------------------------------
void testDoubleList(void) {
    DoubleList *one = dlist_init();
    displayDlist(one);
    
    int a = 10;
    NodeD *node1 = dlist_insert_next(one, NULL, &a, 0);
    
    int b = 30;
    NodeD *node2 = dlist_insert_next(one, NULL, &b, 0);
//    displayDlist(one);
    
    int c = 20;
    NodeD *node3 = dlist_insert_next(one, node1, &c, 1);
    
    int d = 40;
    NodeD *node4 = dlist_insert_next(one, node2, &d, 1);
    displayDlist(one);
    
    void *data;
//    dlist_remove_next(one, NULL, &data, 0);
    dlist_remove_next(one, node2, &data, 1);
    displayDlist(one);
}


// ------------------------------------单向链表----------------------------------------
void testListUnite(void) {
    SingleList *one = init_list(NULL);
    int a = 10;
    list_insert_next(one, NULL, &a);
    int b = 30;
    list_insert_next(one, NULL, &b);
    int c = 50;
    list_insert_next(one, NULL, &c);
//    int d = 70;
//    list_insert_next(one, NULL, &d);
//    int e = 90;
//    list_insert_next(one, NULL, &e);
    displayElements(one);
    
    SingleList *two = init_list(NULL);
    int a2 = 20;
    list_insert_next(two, NULL, &a2);
    int b2 = 40;
    list_insert_next(two, NULL, &b2);
    int c2 = 60;
    list_insert_next(two, NULL, &c2);
//    int d2 = 80;
//    list_insert_next(two, NULL, &d2);
    displayElements(two);
    
    SingleList *list = list_merge(one, two, *match);
    displayElements(list);
}

void testList(void) {
    SingleList *list = init_list(NULL);
    
    printf("%d\n",list->size);
    
    displayElements(list);
    
    int a = 10;
    Node *list1 = list_insert_next(list, NULL, &a);
    int b = 20;
    Node *list2 = list_insert_next(list, NULL, &b);
    int c = 30;
    Node *list3 = list_insert_next(list, NULL, &c);
    int d = 40;
    Node *list4 = list_insert_next(list, NULL, &d);
    int e = 50;
    Node *list5 = list_insert_next(list, NULL, &e);
    displayElements(list);
    printf("--------------------------\n");
    //    int *data;
    //    list_remove_next(list, NULL, (void **)&data);
    //    printf("删除头部元素是：%d\n",*data);
    //    displayElements(list);
    //
    //    list_remove_next(list, list3, (void**)&data);
    //    printf("删除元素位置是4的：%d\n",*data);
    //    displayElements(list);
    //
    //    list_remove_next(list, list3, (void**)&data);
    //    printf("删除元素位置是5的：%d\n",*data);
    //    displayElements(list);
    //    printf("尾部元素：%d\n",*(int*)(list->tail->data));
    
    //    list_destory(list, NULL);
    
//    list_reverse(list);
//    displayElements(list);
    printf("------------------\n");
    
    printf("查找中间的元素----------------\n");
    Node *mid1 = list_midle_element(list);
    printf("%d\n",*(int*)mid1->data);
    
    int f = 60;
    Node *list6 = list_insert_next(list, NULL, &f);
    displayElements(list);
    printf("查找中间的元素----------------\n");
    Node *mid2 = list_midle_element(list);
    printf("%d\n",*(int*)mid2->data);
    
    int g = 70;
    Node *list7 = list_insert_next(list, NULL, &g);
    displayElements(list);
    printf("查找中间的元素----------------\n");
    Node *mid3 = list_midle_element(list);
    printf("%d\n",*(int*)mid3->data);
    
    int h = 80;
    Node *list8 = list_insert_next(list, NULL, &h);
    displayElements(list);
    printf("查找中间的元素----------------\n");
    Node *mid4 = list_midle_element(list);
    printf("%d\n",*(int*)mid4->data);
    
    int i = 90;
    Node *list9 = list_insert_next(list, NULL, &i);
    displayElements(list);
    printf("查找中间的元素----------------\n");
    Node *mid5 = list_midle_element(list);
    printf("%d\n",*(int*)mid5->data);
    
    
    printf("删除倒数第1个元素----------------\n");
    int *data;
    list_remove_rindex_element(list, 1, (void **)&data);
    printf("%d\n",*data);
    displayElements(list);
    
    printf("删除倒数第%d个元素----------------\n",list->size);
    list_remove_rindex_element(list, list->size, (void **)&data);
    printf("%d\n",*data);
    displayElements(list);
    
    printf("删除倒数第2个元素----------------\n");
    list_remove_rindex_element(list, 2, (void **)&data);
    printf("%d\n",*data);
    displayElements(list);
    
    printf("删除倒数第6个元素----------------\n");
    list_remove_rindex_element(list, 6, (void **)&data);
    printf("%d\n",*data);
    displayElements(list);
}
