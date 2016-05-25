#include "Sort.h"

#define PARENT(i) ((i-1)/2)
#define LEFT(i) (i*2+1);
#define RIGHT(i) (i*2+2);

int* merge(int *a1, int *a2, int n1, int n2);
void minimize(int *arr, int len, int i);
void partition(int *arr, int n);

void bubbleSort(int *arr, int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void selectSort(int *arr, int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void mergeSort(int *arr, int n)
{
	if (n <= 1)
	{
		return;
	}
	mergeSort(arr, n / 2);
	mergeSort(arr + n / 2, n - n / 2);
	int *result = merge(arr, arr + n / 2, n / 2, n - n / 2);
	for (int i = 0; i < n; i++)
	{
		*arr++ = *(result+i);
	}
	free(result);
}

void heapSort(int *arr, int n)
{
	if (n <= 1)
	{
		return;
	}

	for (int i = n / 2; i >= 0; i--)
	{
		minimize(arr, n, i);
	}
	heapSort(++arr, n - 1);
}

int* merge(int *a1, int *a2, int n1, int n2)
{
	int *result = (int *)malloc(sizeof(int)*(n1 + n2));
	int *temp = result;
	int i = 0, j = 0;
	while (i < n1 && j < n2)
	{
		if (*a1 < *a2)
		{
			*temp++ = *a1++;
			i++;
		}
		else
		{
			*temp++ = *a2++;
			j++;
		}

	}
	while (i < n1)
	{
		*temp++ = *a1++; 
		i++;
	}
	while (j < n2)
	{
		*temp++ = *a2++;
		j++;
	}
	return result;
}

void minimize(int *arr, int len, int i)
{
	if (i > len / 2)
	{
		return;
	}

	int left = LEFT(i);
	int right = RIGHT(i);
	int min = arr[i];
	int minOne = i;

	if (left < len && min > arr[left])
	{
		min = arr[left];
		minOne = left;
	}
	if (right < len && min > arr[right])
	{
		min = arr[right];
		minOne = right;
	}
	if (minOne != i)
	{
		int temp = arr[i];
		arr[i] = arr[minOne];
		arr[minOne] = temp;
	}
}

void quickSort(int *arr, int n)
{
	if (n < 2)
	{
		return;
	}

	partition(arr, n);
	quickSort(arr, n / 2);
	quickSort(arr + n / 2, n - n / 2);
}

void partition(int *arr, int n)
{
	int pos = rand() / RAND_MAX * n;
	int temp = arr[n - 1];
	arr[n - 1] = arr[pos];
	arr[pos] = temp;

	int middle = 0;
	for (int j = 0; j < n; j++)
	{
		if (arr[j] <= arr[n - 1])
		{
			temp = arr[middle];
			arr[middle] = arr[j];
			arr[j] = temp;
			middle++;
		}
	}
}

void countingSort(int *arr, int n, int max)
{
	int *k = (int *)malloc(sizeof(int)*max);

	for (int i = 0; i < max; i++)	k[i] = 0;
	for (int i = 0; i < n; i++)	k[arr[i]]++;
	for (int i = 1; i < max; i++)	k[i] += k[i - 1];

	int *result = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		int val = arr[i];
		int num = k[val];
		result[num - 1] = val;
		k[val]--;
	}
	for (int i = 0; i < n; i++)	arr[i] = result[i];

	free(k);
	free(result);
}
