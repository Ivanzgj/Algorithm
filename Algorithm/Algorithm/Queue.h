#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>

typedef struct Queue
{
	int head;
	int tail;
	int *queue;
	int capacity;
	int length;
} Queue;

typedef struct PriorityQueue
{
	int head;
	int tail;
	int *queue;
	int capacity;
	int length;
} PriorityQueue;

Queue* initQueue(int capacity);
int isEmpty(Queue *q);
int enqueue(Queue **q, int value);
int dequeue(Queue **q);
void destroyQueue(Queue **q);

PriorityQueue* initPriorityQueue(int capacity);
int isEmpty(PriorityQueue *q);
int insert(PriorityQueue **q, int level);
int pop(PriorityQueue **q);
void destroyPriorityQueue(PriorityQueue **q);

#endif