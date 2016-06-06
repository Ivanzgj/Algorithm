#ifndef __FIBONACI_HEAP_H__
#define __FIBONACI_HEAP_H__

#include <stdlib.h>

#define EMPTY_HEAP INT_MAX

typedef enum FibonaciNodeMark
{
	NONE,
	TRUE,
	FALSE
} FibonaciMark;

typedef struct FibonaciNode
{
	int value;
	int mark;
	int num;
	struct FibonaciNode *left;
	struct FibonaciNode *right;
	struct FibonaciNode *parent;
	struct FibonaciNode *child;
} FibonaciNode;

typedef struct FibonaciHeap
{
	FibonaciNode *min;
	int num;
} FibonaciHeap;

FibonaciHeap *initFibonaciHeap();
int extractMin(FibonaciHeap *heap);
FibonaciNode *insertIntoFibonaciHeap(FibonaciHeap *heap, int value);
void decreaseKey(FibonaciHeap *heap, FibonaciNode *node, int k);
bool deleteFromFibonaciHeap(FibonaciHeap *heap, FibonaciNode *node);
void destroyFibonaciHeap(FibonaciHeap **heap);

#endif