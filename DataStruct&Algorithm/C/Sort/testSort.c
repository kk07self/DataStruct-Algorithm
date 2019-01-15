//
//  testSort.c
//  C
//
//  Created by K K on 2018/12/10.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdio.h>
#include "testSort.h"
#include "sort.h"

void testBubbleSort(void);

void testInsertSort(void);

void testSelectionSort(void);

void testMergeSort(void);

void testQuickSort(void);

void testSort(void) {
//    testBubbleSort();
//    testInsertSort();
//    testSelectionSort();
//    testMergeSort();
    testQuickSort();
}

void testQuickSort(void) {
    int a[13] = {44,22,33,76,77,99,88,11,66,55,56,67,10};
    quickSort(a, 13);
    for (int i = 0; i < 13; i++) {
        printf("%d\n",a[i]);
    }
}

void testMergeSort(void) {
//    int a[10] = {8,6,5,4,7,2,3,1,9,0};
//    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int a[13] = {44,22,33,76,77,99,88,11,66,55,56,67,79};
    mergeSort(a, 13);
    for (int i = 0; i < 13; i++) {
        printf("%d\n",a[i]);
    }
}

void testSelectionSort(void) {
//    int a[10] = {8,6,5,4,7,2,3,1,9,0};
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    selectionSort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n",a[i]);
    }
}

void testInsertSort(void) {
//    int a[10] = {8,6,5,4,7,2,3,1,9,0};
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    insertSort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n",a[i]);
    }
}

void testBubbleSort(void) {
    int a[10] = {8,6,5,4,7,2,3,1,9,0};
//    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    bubbleSort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n",a[i]);
    }
}

