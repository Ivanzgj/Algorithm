#include "Graph.h"
#include "Queue.h"
#include "Stack.h"
#include <stdio.h>

// 以下方法需要输入图时均要求图的顶点编号从1开始！！！

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

	// 初始化
	for (int i = 0; i < vertexNum; i++)
	{
		(vs + i)->weight = INF;
		(vs + i)->p = NULL;
		(vs + i)->f = 0;
	}
	(vs + root - 1)->weight = 0;

	while (1)
	{
		int no = min(vs, vertexNum);	// 找到最短顶点
		if (no == 0)
		{
			break;
		}
		// 更新最短顶点相邻顶点到最小树的距离
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
* 最短路径
*/

void initialize(Graph *g, int s)
{
	Vertex *vs = g->vertex;
	for (int i = 0; i < g->VertexNum; i++)
	{
		Vertex *v = vs + i;
		v->p = NULL;
		v->weight = INF;
		v->f = 0;
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
* 寻找从编号为s的结点开始的关键路径，该方法用于时序图，权重在边上且均为正值
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

/**
* Dijkstra算法，要求所有边的权重均为非负值，结点的编号从1开始
*/
void dijkstra(Graph *g, int **w, int s)
{
	initialize(g, s);

	Vertex *vs = g->vertex;
	GNode *linkTable = g->LinkTable;
	for (int i = 1; i < g->VertexNum; i++)
	{
		int min = INT_MAX;
		int number = 0;
		// 找到目前距离s最短的顶点，该顶点搜索最短距离结束
		for (int j = 0; j < g->VertexNum; j++)
		{
			if (min > (vs + j)->weight && (vs + j)->f == 0)
			{
				min = (vs + j)->weight;
				number = j + 1;
			}
		}
		if (number == 0)	return;
		(vs + number - 1)->f = 1;
		// 加入到各个与number相连的顶点中做松弛更新操作
		GNode *node = (linkTable + number - 1)->next;
		Vertex *u = vs + number - 1;
		while (node != NULL)
		{
			Vertex *v = vs + node->number - 1;
			int weight = *((int*)w + (number - 1)*g->VertexNum + node->number - 1);
			relax(u, v, weight);
			node = node->next;
		}
	}
}

/**
* 根据前驱子图打印i到j的路径，输入顶点编号从1开始，输出顶点编号从1开始
*/
void printIJPath(int **prior, int vertexNum, int i, int j)
{
	i--; j--;
	printf("%d", j + 1);
	int k = *((int*)prior + i*vertexNum + j);
	while (k != -1)
	{
		printf(" <- %d", k + 1);
		k = *((int*)prior + i*vertexNum + k);
	}
	printf("\n");
}

/**
* Floyd 寻找结点对的最短路径算法
* w 权重图
* vertexNum 顶点个数
* lenMatrix 计算结果的最短路径长度存储矩阵（二维）
* priorMatrix 前驱子图（二维），路径<i, ..., j>重点j的前一个顶点k存储在priorMatrix[i][j]中
*/
void Floyd_WallShall(int **w, int vertexNum, int **lenMatrix, int **priorMatrix)
{
	// 初始化
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			*((int*)lenMatrix + i*vertexNum + j) = *((int*)w + i*vertexNum + j);
			if (*((int*)w + i*vertexNum + j) != INF && i != j)
			{
				*((int*)priorMatrix + i*vertexNum + j) = i;
			}
			else
			{
				*((int*)priorMatrix + i*vertexNum + j) = -1;
			}
		}
	}

	// Floyd算法
	for (int k = 0; k < vertexNum; k++)
	{
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				int Dij = *((int*)lenMatrix + i*vertexNum + j);
				int Dik = *((int*)lenMatrix + i*vertexNum + k);
				int Dkj = *((int*)lenMatrix + k*vertexNum + j);
				if (Dik != INF && Dkj != INF && Dij > Dik + Dkj)
				{
					*((int*)lenMatrix + i*vertexNum + j) = Dik + Dkj;
					*((int*)priorMatrix + i*vertexNum + j) = *((int*)priorMatrix + k*vertexNum + j);
				}
			}
		}
	}
}

/**
* 判断结点对是否存在传递闭包
*/
void transitiveClosure(int **w, int vertexNum, int **result)
{
	// 初始化
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			if (*((int*)w + i*vertexNum + j) != INF || i == j)
			{
				*((int*)result + i*vertexNum + j) = 1;
			}
			else
			{
				*((int*)result + i*vertexNum + j) = 0;
			}
		}
	}

	// 应用Floyd算法判断连通性
	for (int k = 0; k < vertexNum; k++)
	{
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				int Dij = *((int*)result + i*vertexNum + j);
				int Dik = *((int*)result + i*vertexNum + k);
				int Dkj = *((int*)result + k*vertexNum + j);
				*((int*)result + i*vertexNum + j) = Dij | (Dik & Dkj);
			}
		}
	}
}

void addSinglePoint(Graph *g, int s)
{
	Vertex *vs = g->vertex;
	GNode *linkTable = g->LinkTable;
	int vertexNum = g->VertexNum;

	Vertex *newVs = (Vertex *)malloc(sizeof(Vertex)* (vertexNum + 1));
	GNode *newLinkTable = (GNode *)malloc(sizeof(GNode)* (vertexNum + 1));
	int i;
	for (i = 0; i < vertexNum; i++)
	{
		newVs[i] = vs[i];
		newLinkTable[i] = linkTable[i];
	}
	newVs[i].number = s;
	GNode *node = (GNode *)malloc(sizeof(GNode));
	node->number = s;
	node->next = NULL;
	GNode *del = node;
	for (i = 0; i < vertexNum; i++)
	{
		GNode *next = (GNode *)malloc(sizeof(GNode));
		next->number = i + 1;
		next->next = NULL;
		node->next = next;
		node = next;
	}
	newLinkTable[i] = *del;
	free(del);

	g->LinkTable = newLinkTable;
	g->vertex = newVs;
	g->VertexNum++;
}

/**
* Johnson算法计算结点对最短路径
*/
bool Johnson(Graph *g, int **w, int **lenMatrix, int **priorMatrix)
{
	// save
	Vertex *vs = g->vertex;
	GNode *linkTable = g->LinkTable;
	int vertexNum = g->VertexNum;

	// add s point
	addSinglePoint(g, g->VertexNum + 1);
	int *newW = (int *)malloc(sizeof(int) * g->VertexNum * g->VertexNum);
	for (int i = 0; i < g->VertexNum; i++)
	{
		for (int j = 0; j < g->VertexNum; j++)
		{
			if (i == g->VertexNum - 1 || j == g->VertexNum - 1)
			{
				*(newW + i*g->VertexNum + j) = 0;
			}
			else
			{
				*(newW + i * g->VertexNum + j) = *((int *)w + i * vertexNum + j);
			}
		}
	}

	// Bellman-Ford算法
	if (Bellman_Ford(g, (int **)newW, g->VertexNum) == false)
	{
		return false;
	}

	Vertex *newVs = g->vertex;
	// recover
	g->LinkTable = linkTable;
	g->vertex = vs;
	g->VertexNum--;
	// 重新赋予权值
	for (int i = 0; i < vertexNum; i++)
	{
		GNode *node = linkTable + i;
		Vertex *u = newVs + i;
		node = node->next;
		while (node != NULL)
		{
			Vertex *v = newVs + node->number - 1;
			if (*((int*)w + i*vertexNum + node->number - 1) != INF)
			{
				*((int*)w + i*vertexNum + node->number - 1) += u->weight - v->weight;
			}
			node = node->next;
		}
	}

	// 反复对每个顶点调用Dijkstra算法计算结点对最短距离
	for (int i = 0; i < vertexNum; i++)
	{
		dijkstra(g, w, i+1);
		Vertex *u = newVs + i;
		for (int j = 0; j < vertexNum; j++)
		{
			Vertex *v = newVs + j;
			*((int*)lenMatrix + i*vertexNum + j) = (g->vertex + j)->weight + v->weight - u->weight;
			if ((g->vertex + j)->p != NULL)
			{
				*((int*)priorMatrix + i*vertexNum + j) = (g->vertex + j)->p->number - 1;
			}
			else
			{
				*((int*)priorMatrix + i*vertexNum + j) = -1;
			}
		}
	}
	return true;
}





/**
* 最大流
*/

// 计算残存网络
void calculateENet(int **c, int vertexNum, int **f, int **e)
{
	for (int i = 0; i < vertexNum; i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			int a = *((int*)c + i*vertexNum + j);
			if (a != 0)
			{
				*((int*)e + i*vertexNum + j) = a - *((int*)f + i*vertexNum + j);
				*((int*)e + j*vertexNum + i) = *((int*)f + i*vertexNum + j);
			}
			else
			{
				*((int*)e + i*vertexNum + j) = 0;
			}
		}
	}
}

// 寻找增广路径
int findRoute(int **e, int vertexNum, int *priorMatrix, int s,int t)
{
	s--; t--;
	int *d = (int *)malloc(sizeof(int)*vertexNum);
	// initialize
	for (int i = 0; i < vertexNum; i++)
	{
		d[i] = 0;
		priorMatrix[i] = -1;
	}
	d[s] = 1;
	// 反复用边<i,j>做松弛操作，将<s,...,j>更新为<s,...,i,j>
	for (int k = 0; k < vertexNum; k++)
	{
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				if (d[j] == 0)
				{
					d[j] |= (d[i] & (*((int*)e + i*vertexNum + j) > 0));
					if (d[j] == 1)
					{
						priorMatrix[j] = i;
					}
				}
			}
		}
	}
	if (d[t] == 0)	return 0;

	int min = INT_MAX;
	int pre = priorMatrix[t];
	while (pre != -1)
	{
		if (min > *((int*)e + pre*vertexNum + t))
		{
			min = *((int*)e + pre*vertexNum + t);
		}
		t = pre;
		pre = priorMatrix[t];
	}
	return min;
}

/**
* Ford-Fulkerson方法的一种实现
* @param c 二维矩阵，记录每条边的容量
* @param vertexNum 顶点个数，包括起点和终点
* @param s 起点编号，编号从1开始
* @param t 终点编号
* @param f 输出流网络矩阵，二维矩阵，记录每条边的流量
*/
void Ford_Fulkerson(int **c, int vertexNum, int s, int t, int **f)
{
	int *e = (int *)malloc(sizeof(int)*vertexNum*vertexNum);	// 残存网络
	int *priorMatrix = (int *)malloc(sizeof(int)*vertexNum);	// 增广路径的前驱子图

	// initialize
	for (int i = 0; i < vertexNum;i++)
	{
		for (int j = 0; j < vertexNum; j++)
		{
			*(f + i*vertexNum + j) = 0;
		}
	}

	while (1)
	{
		calculateENet(c, vertexNum, (int **)f, (int **)e);	// 计算残存网络
		int min;
		if ((min = findRoute((int **)e, vertexNum, priorMatrix, s, t)) == 0)	// 寻找增广路径及其最小流值
		{
			break;
		}
		int pre = priorMatrix[t - 1];
		int next = t - 1;
		while (pre != -1)		// 按增广路径更新流网络
		{
			if (*((int*)c + pre * vertexNum + next) != 0)
			{
				*((int*)f + pre * vertexNum + next) += min;
			}
			else
			{
				*((int*)f + next * vertexNum + pre) -= min;
			}
			next = pre;
			pre = priorMatrix[pre];
		}
	}
}
