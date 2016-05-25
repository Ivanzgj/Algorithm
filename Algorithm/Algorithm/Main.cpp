#include "Sort.h"
#include "Stack.h"
#include "Queue.h"
#include "Tree.h"
#include "DynamicProgramming.h"
#include "BTree.h"
#include <stdio.h>

void testSort();
void testStack();
void testQueue();
void testPriorityQueue();
void testTree();
void testRBTree();
void testAVLTree();
void testHuffmanTree();
void testBTree();
void testDynamicProgramming();

void main()
{
	testBTree();
	system("pause");
}

void testSort()
{
	int arr[15] = { 12, 34, 11, 4, 45, 18, 67, 23, 6, 13, 37, 55, 1, 23, 22 };

	bubbleSort(arr, 15);
	printf("Bubble sort:\n");
	for (int i = 0; i < 15; i++)	printf("%d ", arr[i]);
	printf("\n");

	selectSort(arr, 15);
	printf("Select sort:\n");
	for (int i = 0; i < 15; i++)	printf("%d ", arr[i]);
	printf("\n");

	mergeSort(arr, 15);
	printf("Merge sort:\n");
	for (int i = 0; i < 15; i++)	printf("%d ", arr[i]);
	printf("\n");

	heapSort(arr, 15);
	printf("Heap sort:\n");
	for (int i = 0; i < 15; i++)	printf("%d ", arr[i]);
	printf("\n");

	quickSort(arr, 15);
	printf("Quick sort:\n");
	for (int i = 0; i < 15; i++)	printf("%d ", arr[i]);
	printf("\n");

	countingSort(arr, 15, 100);
	printf("Counting sort:\n");
	for (int i = 0; i < 15; i++)	printf("%d ", arr[i]);
	printf("\n");
}

void testStack()
{
	int arr[11] = { 12, 34, 11, 4, 45, 18, 67, 23, 6, 13, 37 };

	Stack *s = initStack();

	for (int i = 0; i < 11; i++)
	{
		printf("%d ", arr[i]);
		push(&s, arr[i]);
	}
	printf("\n");

	int value;
	while ((value = pop(&s)) != INT_MAX)
	{
		printf("%d ", value);
	}
	printf("\n");

	destroyStack(&s);
}

void testQueue()
{
	int arr[11] = { 12, 34, 11, 4, 45, 18, 67, 23, 6, 13, 37 };

	Queue *q = initQueue(10);

	for (int i = 0; i < 11; i++)
	{
		printf("%d ", arr[i]);
		if (enqueue(&q, arr[i]) == 0)
		{
			printf(" Error Enqueue! ");
		}
	}
	printf("\n");

	int value;
	while ((value = dequeue(&q)) != INT_MAX)
	{
		printf("%d ", value);
	}
	printf("\n");

	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	enqueue(&q, 4);
	printf("%d ", dequeue(&q));
	printf("%d ", dequeue(&q));
	printf("%d ", dequeue(&q));
	enqueue(&q, 5);
	printf("%d ", dequeue(&q));
	printf("%d ", dequeue(&q));
	printf("%d ", dequeue(&q));
	enqueue(&q, 6);
	enqueue(&q, 7);
	printf("%d ", dequeue(&q));

	destroyQueue(&q);
}

void testPriorityQueue()
{
	PriorityQueue *q = initPriorityQueue(10);

	insert(&q, 3);
	insert(&q, 4);
	insert(&q, 2);
	insert(&q, 1);
	printf("%d ", pop(&q));
	printf("%d ", pop(&q));
	printf("%d ", pop(&q));
	insert(&q, 5);
	printf("%d ", pop(&q));
	printf("%d ", pop(&q));
	printf("%d ", pop(&q));
	insert(&q, 6);
	insert(&q, 7);
	printf("%d ", pop(&q));
}

void testTree()
{
	Tree *tree = initTree();
	insertBinarySearchTree(tree, 15);
	insertBinarySearchTree(tree, 32);
	insertBinarySearchTree(tree, 41);
	insertBinarySearchTree(tree, 12);
	insertBinarySearchTree(tree, 14);
	insertBinarySearchTree(tree, 23);
	insertBinarySearchTree(tree, 27);
	insertBinarySearchTree(tree, 34);

	int *order = NULL;
	int n = 0;
	inOrder(tree, &order, &n);
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	printf("\n");
	free(order);

	deleteFromBinarySearchTree(tree, 32);

	inOrder(tree, &order, &n);
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	printf("\n");
	free(order);
	destroyTree(tree);
}

void testRBTree()
{
	Tree *tree = initRBTree();
	insertRBTree(tree, 15);
	insertRBTree(tree, 32);
	insertRBTree(tree, 41);
	insertRBTree(tree, 12);
	insertRBTree(tree, 14);
	insertRBTree(tree, 23);
	insertRBTree(tree, 27);
	insertRBTree(tree, 34);

	int *order = NULL;
	int n = 0;
	inOrderRBTree(tree, &order, &n);
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	printf("\n");
	free(order);

	deleteFromRBTree(tree, 23);

	inOrderRBTree(tree, &order, &n);
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	printf("\n");
	free(order);
	destroyRBTree(tree);
}

void testAVLTree()
{
	Tree *tree = initAVLTree();
	insertAVLTree(tree, 15);
	insertAVLTree(tree, 32);
	insertAVLTree(tree, 41);
	insertAVLTree(tree, 18);
	insertAVLTree(tree, 16);
	insertAVLTree(tree, 23);
	insertAVLTree(tree, 27);
	insertAVLTree(tree, 28);

	int *order = NULL;
	int n = 0;
	inOrder(tree, &order, &n);
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	printf("\n");
	free(order);

	deleteFromAVLTree(tree, 27);

	inOrder(tree, &order, &n);
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	printf("\n");
	free(order);
	destroyAVLTree(tree);
}

void testHuffmanTree()
{
	char c[6] = {'f', 'e', 'c','b', 'd', 'a'};
	int freq[6] = {5, 9, 12, 13, 16, 45};
	Tree *tree = HuffmanTree(c, freq, 6);
	printf("%c\n", HuffmanDecode(tree, "1101"));
}

void testDynamicProgramming()
{
	int *result;
	int *gain;
	int len = 21;
	cutRod(len, &result, &gain);
	printf("各个规模下第一刀的位置：\n");
	for (int i = 0; i <= len; i++)	printf("%d, ", result[i]);
	printf("\n长度为%d下的最大化收益：\n", len);
	printf("%d, ", gain[len]);
	printf("\n长度为%d下的切割方案：\n", len);
	int i = len;
	while (i != 0)
	{
		i = result[i];
		printf("%d, ", len - i);
		len = i;
	}
	printf("\n");
	free(result);
	free(gain);
}

void testBTree()
{
	int keys[10] = {'b','d','q','w','e','a','g','u','k','f'};
	BTree *tree = initBTree(2);
	for (int i = 0; i < 10; i++)	insertBTree(tree, keys[i]);

	deleteFromBTree(tree, 'q');
	deleteFromBTree(tree, 'u');

	destroyBTree(tree);
}
