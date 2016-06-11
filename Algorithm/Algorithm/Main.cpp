#include "Sort.h"
#include "Stack.h"
#include "Queue.h"
#include "Tree.h"
#include "DynamicProgramming.h"
#include "BTree.h"
#include "Graph.h"
#include "FibonaciHeap.h"
#include "Collection.h"
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
void testGraph();
void testPrim();
void testBellmanFord();
void testDagShortestPaths();
void testKeyRoute();
void testDijkstra();
void testFloyd();
void testTransitiveClosure();
void testJohnson();
void testFord();
void testFibonaciHeap();
void testCollection();

void main()
{
	testCollection();
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

void testGraph()
{
	Graph graph;
	graph.VertexNum = 5;
	Vertex v[5];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	graph.vertex = v;

	GNode nodes[5];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode a; a.number = 3; GNode b; b.number = 4; GNode y; y.number = 5; n1.next = &a; a.next = &b; b.next = &y; y.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; n2.next = &c; c.next = &x; x.next = NULL;
	GNode d; d.number = 1; GNode e; e.number = 2; n3.next = &d; d.next = &e; e.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 2; GNode j; j.number = 2; n4.next = &f; f.next = &g; g.next = &j; j.next = NULL;
	GNode h; h.number = 4; GNode i; i.number = 1; n5.next = &h; h.next = &i; i.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;

	searchByWidthFirst(&graph, 5);
	printPath(&graph, 2);

	n1.next = &e; e.next = NULL;
	n2.next = &h; h.next = &f; f.next = NULL;
	n3.next = &g; g.next = NULL;
	n4.next = &y; y.next = NULL;
	n5.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;

	searchByDepthFirst(&graph);
	printf("\n");
	printPath(&graph, 2);

	int *order, n;
	topologySort(&graph, &order, &n);
	printf("\n");
	for (int i = 0; i < n; i++)	printf("%d ", order[i]);
	free(order);
}

void testPrim()
{
	Graph graph;
	graph.VertexNum = 5;
	Vertex v[5];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	graph.vertex = v;

	GNode nodes[5];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode a; a.number = 3; GNode b; b.number = 4; GNode y; y.number = 5; n1.next = &a; a.next = &b; b.next = &y; y.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; n2.next = &c; c.next = &x; x.next = NULL;
	GNode d; d.number = 1; GNode e; e.number = 2; n3.next = &d; d.next = &e; e.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 2; GNode j; j.number = 1; n4.next = &f; f.next = &g; g.next = &j; j.next = NULL;
	GNode h; h.number = 4; GNode i; i.number = 1; n5.next = &h; h.next = &i; i.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;

	int w[5][5] = {	0,			INF,		4,			2,			5,
					INF,		0,			2,			3,			INF,
					4,			2,			0,			INF,		INF,
					2,			3,			INF,		0,			1,
					5,			INF,		INF,		1,			0 };
	int root = 1;
	prim(&graph, (int **)w, root);

	for (int i = 0; i < graph.VertexNum; i++)
	{
		if (i != root - 1)
		{
			Vertex *v = graph.vertex + i;
			printf("(%d, %d) ", v->p->number, v->number);
		}
	}
}

void testBellmanFord()
{
	Graph graph;
	graph.VertexNum = 5;
	Vertex v[5];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	graph.vertex = v;

	GNode nodes[5];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode a; a.number = 2; GNode b; b.number = 4; n1.next = &a; a.next = &b; b.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; GNode z; z.number = 5; n2.next = &c; c.next = &x; x.next = &z; z.next = NULL;
	GNode d; d.number = 2; n3.next = &d; d.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 3; n4.next = &f; f.next = &g; g.next = NULL;
	GNode h; h.number = 1; GNode i; i.number = 3; n5.next = &h; h.next = &i; i.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;

	int w[5][5] = { 0,		6,			INF,		7,		INF,
					INF,	0,			5,			8,		-4,
					INF,	-2,			0,			INF,	INF,
					INF,	INF,		-3,			0,		9,
					2,		INF,		7,			INF,	0 };
	int s = 1;
	if (Bellman_Ford(&graph, (int **)w, s))
	{
		for (int i = 0; i < graph.VertexNum; i++)
		{
			if (i != s - 1)
			{
				Vertex *v = graph.vertex + i;
				printf("路径长度为%d , 路径为 : ", v->weight);
				while (v->p != NULL)
				{
					printf("%d <- ", v->number, v->p->number);
					v = v->p;
				}
				printf("%d\n", s);
			}
		}
	}
}

void testDagShortestPaths()
{
	Graph graph;
	graph.VertexNum = 6;
	Vertex v[6];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	Vertex v6; v6.number = 6; v6.p = NULL; v[5] = v6;
	graph.vertex = v;

	GNode nodes[6];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode n6; n6.number = 6;
	GNode a; a.number = 2; GNode b; b.number = 3; n1.next = &a; a.next = &b; b.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; n2.next = &c; c.next = &x; x.next = NULL;
	GNode d; d.number = 4; GNode aa; aa.number = 5; GNode bb; bb.number = 6; n3.next = &d; d.next = &aa; aa.next = &bb; bb.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 6; n4.next = &f; f.next = &g; g.next = NULL;
	GNode h; h.number = 6; n5.next = &h; h.next = NULL;
	n6.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	nodes[5] = n6;
	graph.LinkTable = nodes;

	int w[6][6] = { 0,			5,		3,			INF,	INF,	INF,
					INF,		0,		2,			6,		INF,	INF,
					INF,		INF,	0,			7,		4,		2,
					INF,		INF,	INF,		0,		-1,		1,
					INF,		INF,	INF,		INF,	0,		-2,
					INF,		INF,	INF,		INF,	INF,	0 };
	int s = 2;
	dagShortestPaths(&graph, (int **)w, s);
	for (int i = 0; i < graph.VertexNum; i++)
	{
		if (i != s - 1)
		{
			Vertex *v = graph.vertex + i;
			if (v->p == NULL)
			{
				printf("结点%d不可从%d到达!\n", v->number, s);
				continue;
			}
			printf("路径长度为%d , 路径为 : ", v->weight);
			while (v->p != NULL)
			{
				printf("%d <- ", v->number, v->p->number);
				v = v->p;
			}
			printf("%d\n", s);
		}
	}
}

void testKeyRoute()
{
	Graph graph;
	graph.VertexNum = 6;
	Vertex v[6];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	Vertex v6; v6.number = 6; v6.p = NULL; v[5] = v6;
	graph.vertex = v;

	GNode nodes[6];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode n6; n6.number = 6;
	GNode a; a.number = 2; GNode b; b.number = 3; n1.next = &a; a.next = &b; b.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; n2.next = &c; c.next = &x; x.next = NULL;
	GNode d; d.number = 4; GNode aa; aa.number = 5; GNode bb; bb.number = 6; n3.next = &d; d.next = &aa; aa.next = &bb; bb.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 6; n4.next = &f; f.next = &g; g.next = NULL;
	GNode h; h.number = 6; n5.next = &h; h.next = NULL;
	n6.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	nodes[5] = n6;
	graph.LinkTable = nodes;

	int w[6][6] = { 0,		5,		3,		INF,	INF,	INF,
					INF,	0,		2,		6,		INF,	INF,
					INF,	INF,	0,		7,		4,		2,
					INF,	INF,	INF,	0,		-1,		1,
					INF,	INF,	INF,	INF,	0,		-2,
					INF,	INF,	INF,	INF,	INF,	0 };
	int s = 1;
	int m = findKeyRoute(&graph, (int **)w, s);
	printPath(&graph, m);
	printf("\n长度：%d\n", -(v + m - 1)->weight);
}

void testDijkstra()
{
	Graph graph;
	graph.VertexNum = 5;
	Vertex v[5];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	graph.vertex = v;

	GNode nodes[5];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode a; a.number = 2; GNode b; b.number = 4; n1.next = &a; a.next = &b; b.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; GNode z; z.number = 5; n2.next = &c; c.next = &x; x.next = &z; z.next = NULL;
	GNode d; d.number = 2; n3.next = &d; d.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 3; n4.next = &f; f.next = &g; g.next = NULL;
	GNode h; h.number = 1; GNode i; i.number = 3; n5.next = &h; h.next = &i; i.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;

	int w[5][5] = { 0,		6,		INF,	7,		INF,
					INF,	0,		5,		8,		4,
					INF,	2,		0,		INF,	INF,
					INF,	INF,	3,		0,		9,
					2,		INF,	7,		INF,	0 };
	int s = 1;
	dijkstra(&graph, (int **)w, s);
	for (int i = 0; i < graph.VertexNum; i++)
	{
		if (i != s - 1)
		{
			Vertex *v = graph.vertex + i;
			printf("路径长度为%d , 路径为 : ", v->weight);
			while (v->p != NULL)
			{
				printf("%d <- ", v->number, v->p->number);
				v = v->p;
			}
			printf("%d\n", s);
		}
	}
}

void testFloyd()
{
	int w[5][5] = {	0,		3,		8,		INF,	-4,
					INF,	0,		INF,	1,		7,
					INF,	4,		0,		INF,	INF,
					2,		INF,	-5,		0,		INF,
					INF,	INF,	INF,	6,		0};
	int lenMatrix[5][5];
	int priorMatrix[5][5];

	Floyd_WallShall((int**)w, 5, (int**)lenMatrix, (int**)priorMatrix);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (lenMatrix[i][j] == INF)
			{
				printf("从%d到%d\t\t长度:INF\n", i + 1, j + 1);
			}
			else
			{
				printf("从%d到%d\t\t长度:%d\t\t路径:", i + 1, j + 1, lenMatrix[i][j]);
				printIJPath((int**)priorMatrix, 5, i + 1, j + 1);
			}
		}
	}
}

void testTransitiveClosure()
{
	int w[5][5] = { 0,		3,		8,		INF,	-4,
					INF,	0,		INF,	1,		7,
					INF,	4,		0,		INF,	INF,
					2,		INF,	-5,		0,		INF,
					INF,	INF,	INF,	6,		0 };
	int result[5][5];

	transitiveClosure((int**)w, 5, (int**)result);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("从%d到%d:%d\n", i + 1, j + 1, result[i][j]);
		}
	}
}

void testJohnson()
{
	Graph graph;
	graph.VertexNum = 5;
	Vertex v[5];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	graph.vertex = v;

	GNode nodes[5];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode a; a.number = 2; GNode b; b.number = 3; GNode bb; bb.number = 5; n1.next = &a; a.next = &b; b.next = &bb; bb.next = NULL;
	GNode x; x.number = 4; GNode z; z.number = 5; n2.next = &x; x.next = &z; z.next = NULL;
	GNode d; d.number = 2; n3.next = &d; d.next = NULL;
	GNode f; f.number = 1; GNode g; g.number = 3; n4.next = &f; f.next = &g; g.next = NULL;
	GNode h; h.number = 4; n5.next = &h; h.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;

	int w[5][5] = { 0,		3,		8,		INF,	-4,
					INF,	0,		INF,	1,		7,
					INF,	4,		0,		INF,	INF,
					2,		INF,	-5,		0,		INF,
					INF,	INF,	INF,	6,		0 };
	int lenMatrix[5][5];
	int priorMatrix[5][5];

	if (Johnson(&graph, (int**)w, (int**)lenMatrix, (int**)priorMatrix))
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (lenMatrix[i][j] == INF)
				{
					printf("从%d到%d\t\t长度:INF\n", i, j);
				}
				else
				{
					printf("从%d到%d\t\t长度:%d\t\t路径:", i, j, lenMatrix[i][j]);
					printIJPath((int**)priorMatrix, 5, i + 1, j + 1);
				}
			}
		}
	}
}

void testFord()
{
	int c[6][6] = {	0,		16,		13,		0,		0,		0,
					0,		0,		0,		12,		0,		0,
					0,		4,		0,		0,		14,		0,
					0,		0,		9,		0,		0,		20,
					0,		0,		0,		7,		0,		4,
					0,		0,		0,		0,		0,		0	};
	int f[6][6];
	Ford_Fulkerson((int **)c, 6, 1, 6, (int **)f);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			int flow = f[i][j];
			if (flow != 0)
			{
				printf("%d -> %d : %d\n", i + 1, j + 1, flow);
			}
		}
	}
}

void testFibonaciHeap()
{
	FibonaciHeap *h = initFibonaciHeap();

	insertIntoFibonaciHeap(h, 10);
	insertIntoFibonaciHeap(h, 3);
	FibonaciNode *node = insertIntoFibonaciHeap(h, 12);
	insertIntoFibonaciHeap(h, 5);
	insertIntoFibonaciHeap(h, 11);
	printf("%d\n", extractMin(h));

	printf("%d\n", deleteFromFibonaciHeap(h, node));

	destroyFibonaciHeap(&h);
}

void testCollection()
{
	Set *set = initSet(0x01);
	Set *set1 = insert(set, 12);
	Set *set2 = insert(set1, 10);
	Set *set3 = insert(set2, 11);
	Set *set4 = insert(set3, 16);
	Set *set5 = insert(set4, 18);
	Set *set6 = remove(set5);
	printf("set after remove = %d\n", set6->member);
	Set *set7 = findSet(set);
	printf("set after findSet = %d\n", set7->member);
}
