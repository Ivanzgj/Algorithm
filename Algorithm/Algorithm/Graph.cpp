#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include <stdio.h>

/**
* 广度优先搜索，要求输入图g的结点编号从1开始
*/
void searchByWidthFirst(Graph *g, int start)
{
	int VertexNum = g->VertexNum;
	Queue *q = initQueue(VertexNum);
	Vertex *vs = g->vertex;
	GNode *linkTable = g->LinkTable;
	Vertex *s = vs + start - 1;

	for (int i = 0; i < VertexNum; i++)
	{
		Vertex *v = vs + i;
		v->color = Vertex_WHITE;
	}

	s->color = Vertex_GRAY;
	s->p = NULL;
	enqueue(&q, s->number);
	while (!isEmpty(q))
	{
		int number = dequeue(&q);
		Vertex *u = vs + number - 1;
		GNode *links = linkTable + number - 1;
		links = links->next;
		while (links != NULL)
		{
			Vertex *v = vs + links->number - 1;
			if (v->color == Vertex_WHITE)
			{
				v->color = Vertex_GRAY;
				v->p = u;
				enqueue(&q, links->number);
			}
			links = links->next;
		}
		u->color = Vertex_BLACK;
	}
}

void searchByDepthFirst(Graph *g)
{
	int VertexNum = g->VertexNum;
	Stack *stack = initStack();
	Vertex *vs = g->vertex;
	GNode *linkTable = g->LinkTable;
	int order = 0;

	for (int i = 0; i < VertexNum; i++)
	{
		Vertex *v = vs + i;
		v->color = Vertex_WHITE;
		v->p = NULL;
		push(&stack, v->number);
	}

	while (!isEmpty(stack))
	{
		int number = pop(&stack);
		Vertex *u = vs + number - 1;
		if (u->color == Vertex_WHITE) 
		{
			u->color = Vertex_GRAY;
			push(&stack, number);
		}
		else if (u->color == Vertex_GRAY)
		{
			u->color = Vertex_BLACK;
			u->f = order++;
			continue;
		}
		else
		{
			continue;
		}
		GNode *links = linkTable + number - 1;
		links = links->next;
		while (links != NULL)
		{
			Vertex *v = vs + links->number - 1;
			if (v->color == Vertex_WHITE)
			{
				v->p = u;
				push(&stack, links->number);
			}
			links = links->next;
		}
	}
}

// 要求输入图的结点编号从1开始
void printPath(Graph *g, int vertex)
{
	Vertex *vs = g->vertex;
	Vertex *v = vs + vertex - 1;
	
	while (v != NULL)
	{
		printf("%d ", v->number);
		v = v->p;
	}
}

void topologySort(Graph *g, int **order, int *n)
{
	searchByDepthFirst(g);
	*n = g->VertexNum;
	*order = (int *)malloc(sizeof(int) * *n);
	for (int i = 0; i < *n; i++)
	{
		(*order)[*n - 1 - g->vertex[i].f] = i + 1;
	}
}
