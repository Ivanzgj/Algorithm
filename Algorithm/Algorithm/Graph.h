#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>

typedef enum VertexColor
{
	Vertex_WHITE = 0,	// 未被搜索到
	Vertex_BLACK = 1,	// 子结点都被搜索完毕
	Vertex_GRAY = 2	// 子结点正在被搜索
} VertexColor;

typedef struct GNode
{
	int number;
	struct GNode *next;
} GNode;

typedef struct Vertex
{
	int number;
	int weight;		// 边(p, v)的权重
	int f;			// 深度优先搜索中标记完成搜索的次序/排名
	VertexColor color;	// 搜索过程标记搜索状态
	struct Vertex *p;
} Vertex;

typedef struct Graph
{
	GNode *LinkTable;
	Vertex *vertex;
	int VertexNum;
} Graph;

void searchByWidthFirst(Graph *g, int start);
void searchByDepthFirst(Graph *g);
void printPath(Graph *g, int vertex);
void topologySort(Graph *g, int **order, int *n);

#endif