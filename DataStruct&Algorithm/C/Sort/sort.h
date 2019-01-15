//
//  sort.h
//  C
//
//  Created by K K on 2018/12/10.
//  Copyright © 2018 K K. All rights reserved.
//

#ifndef sort_h
#define sort_h

#include <stdio.h>


/**
 冒泡排序-----
 时间复杂度：最坏 O(n),最差O(n²)

 @param a 要排序的数组
 @param n 数组个数
 */
void bubbleSort(int a[], int n);



/**
 插入排序----------------
 时间复杂度：最坏 O(n),最差O(n²)

 @param a 要排序的数组
 @param n 数组个数
 */
void insertSort(int a[], int n);


/**
 选择排序-----------------
 时间复杂度：最坏 O(n²),最差O(n²)

 @param a 要排序的数组
 @param n 数组个数
 */
void selectionSort(int a[], int n);


/**
 归并排序------------------
 时间复杂度：nlgn

 @param a 要排序的数组
 @param n 数组个数
 */
void mergeSort(int a[], int n);


/**
 快速排序-------------------
 时间复杂度：最坏 O(n²), 最好O(nlgn)
 
 @param a 要排序的数组
 @param n 数组个数
 */
void quickSort(int a[], int n);
#endif /* sort_h */
