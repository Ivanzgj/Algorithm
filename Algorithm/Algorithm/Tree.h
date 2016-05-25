#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>

typedef enum RBNodeColor
{
	RED = 0,
	BLACK = 1
} RBNodeColor;

typedef struct Node
{
	int value;
	int size;
	int height;	//该结点的树高，用于AVL树
	int color;	// 结点颜色，用于红黑色
	char name;	// 结点名称，用于HuffmanTree
	struct Node *parent;
	struct Node *left;
	struct Node *right;
} Node;

typedef struct Tree
{
	Node *root;
	Node *nil;	// 哨兵，用于红黑树
} Tree;

/**
* 一般二叉树
*/

Tree* initTree();
void destroyTree(Tree *tree);
int getSize(Tree *tree);
void inOrder(Tree *tree, int **order, int *num);


/**
* 二叉搜索树
*/
Node* minimum(Tree *tree);
Node* maximum(Tree *tree);
void insertBinarySearchTree(Tree *tree, int value);
void deleteFromBinarySearchTree(Tree *tree, Node *node);
void deleteFromBinarySearchTree(Tree *tree, int value);




/**
* 红黑树
*/

Tree* initRBTree();
void destroyRBTree(Tree *tree);
void insertRBTree(Tree *tree, int value);
void deleteFromRBTree(Tree *tree, Node *node);
void deleteFromRBTree(Tree *tree, int value);
void inOrderRBTree(Tree *tree, int **order, int *num);



/*
* AVL树
*/

Tree* initAVLTree();
void destroyAVLTree(Tree *tree);
void insertAVLTree(Tree *tree, int value);
void deleteFromAVLTree(Tree *tree, Node *node);
void deleteFromAVLTree(Tree *tree, int value);




/**
* Huffman Code
*/

Tree* HuffmanTree(char *collection, int *frequency, int num);
char HuffmanDecode(Tree *tree, char *code);



#endif