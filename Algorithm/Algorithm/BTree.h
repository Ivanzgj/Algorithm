#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdlib.h>

typedef struct LinkKey
{
	int key;
	struct LinkKey *next;
} LinkKey;

typedef struct LinkNode
{
	void *node;
	struct LinkNode *next;
} LinkNode;

typedef struct BNode
{
	int n;	// 孩子个数，so key个数为n-1
	bool leaf;
	LinkKey *key;
	LinkNode *children;
	struct BNode *parent;
} BNode;

typedef struct BTree
{
	BNode *root;
	int t;	// B树的最小度数
} Btree;



BTree *initBTree(int t);
void destroyBTree(BTree *tree);
void insertBTree(BTree *tree, int key);
void deleteFromBTree(BTree *tree, int key);

#endif