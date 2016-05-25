#include "Queue.h"

#define PARENT(i) ((i-1)/2)

/**
* 以下为使用数组实现的循环队列
*/

Queue* initQueue(int capacity)
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	int *queue = (int *)malloc(sizeof(int)*capacity);
	q->head = q->tail = 0;
	q->queue = queue;
	q->capacity = capacity;
	q->length = 0;
	return q;
}

int isEmpty(Queue *q)
{
	if (q->length != 0)
	{
		return 0;
	}
	return 1;
}

int enqueue(Queue **q, int value)
{
	Queue *tmp = *q;

	if (tmp->length == tmp->capacity)
	{
		return 0;
	}

	tmp->queue[tmp->tail] = value;
	tmp->tail = (tmp->tail + 1) % tmp->capacity;
	tmp->length++;

	return 1;
}

int dequeue(Queue **q)
{
	if (isEmpty(*q) == 1)
	{
		return INT_MAX;
	}

	Queue *tmp = *q;
	int pos = (tmp->head + 1) % tmp->capacity;
	int value = tmp->queue[tmp->head];
	tmp->head = pos;
	tmp->length--;
	return value;
}

void destroyQueue(Queue **q)
{
	free((*q)->queue);
	free(*q);
	*q = NULL;
}


/**
* 以下为利用堆实现的优先队列
* 其insert方法使用最大堆调整插入的数据
* 其它方法与上述循环队列相同
*/

void priority(PriorityQueue *q);
void adjust(int *arr, int head, int length, int capacity);

PriorityQueue* initPriorityQueue(int capacity)
{
	PriorityQueue *q = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	int *queue = (int *)malloc(sizeof(int)*capacity);
	q->head = q->tail = 0;
	q->queue = queue;
	q->capacity = capacity;
	q->length = 0;
	return q;
}

int isEmpty(PriorityQueue *q)
{
	if (q->length != 0)
	{
		return 0;
	}
	return 1;
}

int insert(PriorityQueue **q, int level)
{
	PriorityQueue *tmp = *q;

	if (tmp->length == tmp->capacity)
	{
		return 0;
	}

	tmp->queue[tmp->tail] = level;
	tmp->tail = (tmp->tail + 1) % tmp->capacity;
	tmp->length++;
	priority(tmp);

	return 1;
}

int pop(PriorityQueue **q)
{
	if (isEmpty(*q) == 1)
	{
		return INT_MAX;
	}

	PriorityQueue *tmp = *q;
	int pos = (tmp->head + 1) % tmp->capacity;
	int level = tmp->queue[tmp->head];
	tmp->head = pos;
	tmp->length--;
	return level;
}

void destroyPriorityQueue(PriorityQueue **q)
{
	free((*q)->queue);
	free(*q);
	*q = NULL;
}

void priority(PriorityQueue *q)
{
	adjust(q->queue, q->head, q->length, q->capacity);
}

void adjust(int *arr, int head, int length, int capacity)
{
	int tail = (head + length - 1) % capacity;
	int parent = (PARENT(length - 1) + head) % capacity;
	while (parent <= head && arr[tail] > arr[parent])
	{
		int temp = arr[tail];
		arr[tail] = arr[parent];
		arr[parent] = temp;

		tail = parent;
		if (tail < head)
		{
			parent = (PARENT(tail + capacity - head) + head) % capacity;
		}
		else
		{
			parent = PARENT(tail - head) + head;
		}
	}
}
