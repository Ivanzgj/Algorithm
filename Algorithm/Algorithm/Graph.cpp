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

/**
* 深度优先搜索，要求输入图g的结点编号从1开始
*/
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
			// 开始搜索该结点的子结点
			u->color = Vertex_GRAY;
			push(&stack, number);
		}
		else if (u->color == Vertex_GRAY)
		{
			// 该结点的子结点已经被搜索完了
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
			// 展开子结点并入栈
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

/**
* 有向无环图的拓扑排序
*/
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



/**
* 最小生成树
*/

int min(Vertex *vs, int num);

// 输入图g的结点编号从1开始
void prim(Graph *g, int **w, int root)
{
	Vertex *vs = g->vertex;
	GNode *links = g->LinkTable;
	int vertexNum = g->VertexNum;

	for (int i = 0; i < vertexNum; i++)
	{
		(vs + i)->weight = INF;
		(vs + i)->p = NULL;
		(vs + i)->f = 0;
	}
	(vs + root - 1)->weight = 0;

	while (1)
	{
		int no = min(vs, vertexNum);
		if (no == 0)
		{
			break;
		}
		Vertex *u = vs + no - 1;
		u->f = 1;
		GNode *link = links + no - 1;
		link = link->next;
		while (link != NULL)
		{
			int weight = *((int *)w + (no - 1)*vertexNum + link->number - 1);
			Vertex *v = vs + link->number - 1;
			if (v->f == 0 && weight < v->weight)
			{
				v->weight = weight;
				v->p = u;
			}
			link = link->next;
		}
	}
}

int min(Vertex *vs, int num)
{
	int min = INT_MAX;
	int m = -1;
	for (int i = 0; i < num; i++)
	{
		if ((vs + i)->f == 0 && (vs + i)->weight < min)
		{
			min = (vs + i)->weight;
			m = i;
		}
	}
	return m + 1;
}
