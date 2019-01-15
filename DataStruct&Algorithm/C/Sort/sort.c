//
//  sort.c
//  C
//
//  Created by K K on 2018/12/10.
//  Copyright © 2018 K K. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void bubbleSort(int a[], int n) {
    if (n <= 1) {
        return;
    }
    
    int temp;
    for (int j = 0; j<n-1; j++) {
        int i = 0;
        int flag = 0;
        while (i < n-1) {
            if (a[i] > a[i+1]) { // 前者大于后者，交换
                flag = 1;
                temp = a[i+1];
                a[i+1] = a[i];
                a[i] = temp;
            }
            i++;
        }
        if (flag == 0) { // 一圈下来未进行交换，说明已经是排序好的
            printf("只进行了一轮循环---------\n");
            return;
        }
    }
    
}

void insertSort(int a[], int n) {
    if (n <= 1) {
        return;
    }
    
    int temp;
    for (int i = 1; i<n; i++) {
        int j = i;
        while (j>0) {
            if (a[j]<a[j-1]) { // 如果后面一个数据小于之前一个，进行数据交换
                // 数据交换
                temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
                j--;
            } else {
                // 当前循环遍历结束----------插入排序优于冒泡排序的部分就是这里
                break;
            }
        }
    }
}


void selectionSort(int a[], int n) {
    if (n <= 1) {
        return;
    }
    
    int temp;
    for (int i = 0; i<n-1; i++) {
        int flag = i;
        
        for (int j = i+1; j<n; j++) { // 从i之后选出最小的一个数插入到当前遍历到的位置
            if (a[flag]>a[j]) {
                flag = j;
            }
        }
        
        // 每一轮选择结束后数据交换
        temp = a[i];
        a[i] = a[flag];
        a[flag] = temp;
    }
}

// -------------------------------------------归并排序-------------------------------------

// 合并函数
void merge(int a[], int begin, int middle, int end) {

    int *temp; // 创建一个临时数组，用于存储两个分区比较后的数组元素
    if ((temp = (int *)malloc(sizeof(int)*(end-begin+1))) == NULL) {
        return;
    }
    int i = begin, j = middle+1, tflag = 0;
    
    // begin~middle是左侧分区，i来标记左侧分区的遍历下标；middle+1是右侧分区，j标记右侧分区的下标
    while (i<=middle && j<=end) {
        if (a[i]<a[j]) {
            temp[tflag++] = a[i++];
        } else {
            temp[tflag++] = a[j++];
        }
    }
    
    // 处理没有遍历完的部分
    if (i <= middle) { // 如果i<=middle，说明i还满足条件未赋值完
        for (; i<=middle; i++) {
            temp[tflag++] = a[i];
        }
    } else {
        for (; j<=end; j++) {
            temp[tflag++] = a[j];
        }
    }
    
    // 将temp中的元素替换进入原数组中
    for (int i = begin, j = 0; i<= end;) {
        a[i++] = temp[j++];
    }
    free(temp);
}


// 递归调用函数
void mergeSort_c(int a[], int begin, int end){
    if (end <= begin) {
        return;
    }
    // 取出begin和end的中间值
    int middle = (begin + end)/2;
    mergeSort_c(a, begin, middle); // 归并排序左侧分区
    mergeSort_c(a, middle+1, end); // 归并排序右侧分区
    merge(a, begin, middle, end);
}

void mergeSort(int a[], int n) {
    mergeSort_c(a, 0, n-1);
}


// ---------------------------------------------快速排序------------------------

// 获取分区点
int partition(int a[], int begin, int end) {
    int i = begin, j = begin;
    int temp;
    for (; j<end; j++) {
        if (a[j]<a[end]) {
            if (i != j) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            i++;
        }
    }
    temp = a[i];
    a[i] = a[end];
    a[end] = temp;
    return i;
}


void quickSort_c(int a[], int begin, int end) {
    if (begin>=end) {
        return;
    }
    int middle = partition(a, begin, end);
    quickSort_c(a, begin, middle-1);
    quickSort_c(a, middle+1, end);
}

void quickSort(int a[], int n) {
    if (n == 1) {
        return;
    }
    
    quickSort_c(a, 0, n-1);
}


