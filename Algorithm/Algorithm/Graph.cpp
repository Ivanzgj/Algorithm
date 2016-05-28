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

// prim算法，输入图g的结点编号从1开始
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





/**
* 单源最短路径
*/

void initialize(Graph *g, int s)
{
	Vertex *vs = g->vertex;
	for (int i = 0; i < g->VertexNum; i++)
	{
		Vertex *v = vs + i;
		v->p = NULL;
		v->weight = INF;
	}
	(vs + s - 1)->weight = 0;
}

// 松弛操作，检查<s, ..., v>的距离是否比<s, ..., u, v>大，是则更新<s, ..., v>为<s, ..., u, v>
void relax(Vertex *u, Vertex *v, int w)
{
	if (u->weight == INF || w == INF)	return;
	if (v->weight > u->weight + w)
	{
		v->weight = u->weight + w;
		v->p = u;
	}
}

/**
* Bellman Ford 单源最短路径算法
* @return true 没有负环路； false 有负环路，最短路径构造失败
*/
bool Bellman_Ford(Graph *g, int **w, int s)
{
	initialize(g, s);

	GNode *linkTable = g->LinkTable;
	for (int i = 1; i < g->VertexNum; i++)
	{
		// 反复将边加入到已有的最小路径图中，检查是否有更优路径
		for (int j = 0; j < g->VertexNum; j++)
		{
			GNode *node = (linkTable + j)->next;
			Vertex *u = g->vertex + j;
			while (node != NULL)
			{
				Vertex *v = g->vertex + node->number - 1;
				int weight = *((int*)w + j * g->VertexNum + node->number - 1);
				relax(u, v, weight);
				node = node->next;
			}
		}
	}

	// 通过检查是否都已达到最短路径来检查是否存在负环路
	for (int j = 0; j < g->VertexNum; j++)
	{
		GNode *node = (linkTable + j)->next;
		Vertex *u = g->vertex + j;
		while (node != NULL)
		{
			Vertex *v = g->vertex + node->number - 1;
			int weight = *((int*)w + j * g->VertexNum + node->number - 1);
			if (v->weight > u->weight + weight)
			{
				return false;
			}
			node = node->next;
		}
	}
	return true;
}

/**
* 有向无环图的单源最短路径，基于拓扑排序的顺序进行松弛操作
*/
void dagShortestPaths(Graph *g, int **w, int s)
{
	int *order, n;
	GNode *linkTable = g->LinkTable;
	Vertex *vs = g->vertex;

	topologySort(g, &order, &n);

	initialize(g, s);

	for (int i = 0; i < n; i++)
	{
		int number = order[i];
		GNode *node = linkTable + number - 1;
		node = node->next;
		Vertex *u = vs + number - 1;
		while (node != NULL)
		{
			Vertex *v = vs + node->number - 1;
			int weight = *((int*)w + (number - 1) * g->VertexNum + node->number - 1);
			relax(u, v, weight);
			node = node->next;
		}
	}
}

/**
* 寻找从编号为s的结点开始的关键路径，该方法用于时序图，权重位于结点上而不是边上，而且权重均为正值
* @return 关键路径的最后一个结点的编号，可以据此调用printPath方法打印关键路径
*/
int findKeyRoute(Graph *g, int **w, int s)
{
	for (int i = 0; i < g->VertexNum; i++)
	{
		for (int j = 0; j < g->VertexNum; j++)
		{
			*((int*)w + i*g->VertexNum + j) *= -1;
		}
	}

	dagShortestPaths(g, w, s);

	Vertex *vs = g->vertex;
	int m = 0;
	int min = INT_MAX;
	for (int i = 0; i < g->VertexNum; i++)
	{
		if (min > (vs + i)->weight)
		{
			m = i;
			min = (vs + i)->weight;
		}
	}
	return m + 1;
}
