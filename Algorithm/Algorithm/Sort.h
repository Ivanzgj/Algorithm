#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>

void bubbleSort(int *arr, int n);
void selectSort(int *arr, int n);
void mergeSort(int *arr, int n);
void heapSort(int *arr, int n);
void quickSort(int *arr, int n);
void countingSort(int *arr, int n, int max);

#endif