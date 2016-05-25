#include "Tree.h"

/**
* 以下是二叉树的基本操作
*/

Node *createNode(int value);
void destroyNode(Node *node);
void transplant(Tree *tree, Node *tree1, Node *tree2);
void inOrder(Node *node, int **order, int *i);

Tree* initTree()
{
	Tree *tree = (Tree *)malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

Node *createNode(int value)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->value = value;
	node->size = 1;
	return node;
}

void destroyTree(Tree *tree)
{
	destroyNode(tree->root);
	tree->root = NULL;
}

int getSize(Tree *tree)
{
	Node *root = tree->root;
	if (root == NULL)	return 0;
	return root->size;
}

void inOrder(Tree *tree, int **order, int *num)
{
	*num = tree->root->size;
	*order = (int *)malloc(sizeof(int) * *num);
	int i = 0;
	inOrder(tree->root, order, &i);
}

void inOrder(Node *node, int **order, int *i)
{
	if (node == NULL)
	{
		return;
	}

	inOrder(node->left, order, i);
	(*order)[*i] = node->value;
	(*i)++;
	inOrder(node->right, order, i);
}

/**
* 将*tree1替换成tree2，若*tree1为根，则直接改变tree->root指向
*/
void transplant(Tree *tree, Node *tree1, Node *tree2)
{
	if (tree1->parent == NULL)
	{
		tree->root = tree2;
		tree2->parent = NULL;
		return;
	}

	if (tree2 != NULL)					tree2->parent = tree1->parent;
	if (tree1 == tree1->parent->left)	tree1->parent->left = tree2;
	else								tree1->parent->right = tree2;
}






/**
* 以下是二叉搜索树的操作
*/

Node *getNode(Node *root, int value);

Node* minimum(Tree *tree)
{
	Node *n = tree->root;
	if (n == NULL)	return NULL;
	while (n->left != NULL)	n = n->left;
	return n;
}

Node* maximum(Tree *tree)
{
	Node *n = tree->root;
	if (n == NULL)	return NULL;
	while (n->right != NULL)	n = n->right;
	return n;
}

void destroyNode(Node *node)
{
	if (node != NULL)
	{
		Node *left = node->left;
		Node *right = node->right;
		free(node);
		destroyNode(left);
		destroyNode(right);
	}
}

void insertBinarySearchTree(Tree *tree, int value)
{
	if (tree->root == NULL)
	{
		tree->root = createNode(value);
		return;
	}

	Node *node = createNode(value);
	Node *n = tree->root;
	while (1)
	{
		n->size++;
		if (value < n->value)
		{
			if (n->left == NULL)
			{
				n->left = node;
				node->parent = n;
				break;
			}
			n = n->left;
		}
		else
		{
			if (n->right == NULL)
			{
				n->right = node;
				node->parent = n;
				break;
			}
			n = n->right;
		}
	}
}

void deleteFromBinarySearchTree(Tree *tree, Node *node)
{
	if (node == NULL)	return;

	Node *n = node;
	while (n->parent != NULL)
	{
		n = n->parent;
		n->size--;
	}

	if (node->left == NULL)
	{
		transplant(tree, node, node->right);
	}
	else if (node->right == NULL)
	{
		transplant(tree, node, node->left);
	}
	else
	{
		Tree t;
		t.root = node->right;
		Node *min = minimum(&t);
		Node *end = min->right;
		min->size = node->size - 1;
		if (node == tree->root)	tree->root = min;

		if (node->right != min)
		{
			transplant(tree, min, min->right);
			min->right = node->right;
			node->right->parent = min;
		}
		min->left = node->left;
		node->left->parent = min;
		transplant(tree, node, min);
		
		n = min->right;
		while (n != end)
		{
			n->size--;
			n = n->left;
		}
	}

	free(node);
}

void deleteFromBinarySearchTree(Tree *tree, int value)
{
	Node *node = getNode(tree->root, value);
	deleteFromBinarySearchTree(tree, node);
}

Node *getNode(Node *root, int value)
{
	if (root == NULL)	return NULL;
	if (root->value == value)	return root;
	Node *node = getNode(root->left, value);
	if (node != NULL)	return node;
	node = getNode(root->right, value);
	return node;
}



/**
* 以下是红黑树的操作
* 其重写了二叉树的基本操作，因为红黑树使用了哨兵结点nil代替NULL
*/

void leftRotate(Tree *tree, Node *x);
void rightRotate(Tree *tree, Node *x);
Node* createRBNode(Tree *tree, int value);
void RBInsertFixup(Tree *tree, Node *z);
void RBDeleteFixup(Tree *tree, Node *x);
void inOrderRBTree(Tree *tree, Node *node, int **order, int *i);
void RBTransplant(Tree *tree, Node *tree1, Node *tree2);
Node *getRBNode(Tree *tree, Node *root, int value);
Node* RBMinimum(Tree *tree);
Node* RBMaximum(Tree *tree);

Tree* initRBTree()
{
	Tree *tree = initTree();
	tree->nil = (Node *)malloc(sizeof(Node));
	tree->nil->color = BLACK;
	return tree;
}

void destroyRBTree(Tree *tree)
{
	free(tree->nil);
	destroyTree(tree);
}

void insertRBTree(Tree *tree, int value)
{
	if (tree->root == NULL)
	{
		tree->root = createRBNode(tree, value);
		RBInsertFixup(tree, tree->root);
		return;
	}

	Node *node = createRBNode(tree, value);
	Node *n = tree->root;
	while (1)
	{
		n->size++;
		if (value < n->value)
		{
			if (n->left == tree->nil)
			{
				n->left = node;
				node->parent = n;
				break;
			}
			n = n->left;
		}
		else
		{
			if (n->right == tree->nil)
			{
				n->right = node;
				node->parent = n;
				break;
			}
			n = n->right;
		}
	}

	RBInsertFixup(tree, node);
}

void deleteFromRBTree(Tree *tree, Node *node)
{
	if (node == tree->nil)	return;

	int node_original_color = node->color;
	Node *changeNode = node;

	Node *n = node;
	while (n->parent != tree->nil)
	{
		n = n->parent;
		n->size--;
	}

	if (node->left == tree->nil)
	{
		changeNode = node->right;
		transplant(tree, node, node->right);
	}
	else if (node->right == tree->nil)
	{
		changeNode = node->left;
		transplant(tree, node, node->left);
	}
	else
	{
		Tree t;
		t.root = node->right;
		t.nil = tree->nil;
		Node *min = RBMinimum(&t);
		Node *end = min->right;

		node_original_color = min->color;
		changeNode = end;

		min->size = node->size - 1;
		if (node == tree->root)	tree->root = min;

		if (node->right != min)
		{
			RBTransplant(tree, min, min->right);
			min->right = node->right;
			node->right->parent = min;
		}
		min->left = node->left;
		node->left->parent = min;
		RBTransplant(tree, node, min);

		n = min->right;
		while (n != end)
		{
			n->size--;
			n = n->left;
		}

		min->color = node->color;
	}

	free(node);

	if (node_original_color == BLACK)
	{
		RBDeleteFixup(tree, changeNode);
	}
}

void deleteFromRBTree(Tree *tree, int value)
{
	Node *node = getRBNode(tree, tree->root, value);
	deleteFromRBTree(tree, node);
}

void leftRotate(Tree *tree, Node *x)
{
	Node *y = x->right;

	x->right = y->left;
	if (y->left != tree->nil && y->left != NULL)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == tree->nil || x->parent == NULL)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

	y->size = x->size;
	x->size -= ((y->right != tree->nil && y->right != NULL) ? y->right->size : 0) + 1;
}

void rightRotate(Tree *tree, Node *x)
{
	Node *y = x->left;

	x->left = y->right;
	if (y->right != tree->nil && y->right != NULL)
	{
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == tree->nil || x->parent == NULL)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;

	y->size = x->size;
	x->size -= ((y->left != tree->nil && y->left != NULL) ? y->left->size : 0) + 1;
}

Node* createRBNode(Tree *tree, int value)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->size = 1;
	node->color = RED;
	node->left = tree->nil;
	node->right = tree->nil;
	node->parent = tree->nil;
	return node;
}

void RBInsertFixup(Tree *tree, Node *z)
{
	while (z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left)
		{
			Node *y = z->parent->parent->right;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					z = z->parent;
					leftRotate(tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightRotate(tree, z->parent->parent);
			}
		}
		else if (z->parent == z->parent->parent->right)
		{
			// 与上面对称
			Node *y = z->parent->parent->left;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					rightRotate(tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate(tree, z->parent->parent);
			}
		}
	}
	tree->root->color = BLACK;
}

void RBDeleteFixup(Tree *tree, Node *x)
{
	while (x != tree->root && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			Node *w = x->parent->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(tree,x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(tree, x->parent);
				x = tree->root;
			}
		}
		else if (x == x->parent->right)
		{
			// 与上面对称
			Node *w = x->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(tree, x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(tree, x->parent);
				x = tree->root;
			}
		}
	}
	x->color = BLACK;
}

void inOrderRBTree(Tree *tree, int **order, int *num)
{
	*num = tree->root->size;
	*order = (int *)malloc(sizeof(int)* *num);
	int i = 0;
	inOrderRBTree(tree, tree->root, order, &i);
}

void inOrderRBTree(Tree *tree, Node *node, int **order, int *i)
{
	if (node == tree->nil)
	{
		return;
	}

	inOrderRBTree(tree, node->left, order, i);
	(*order)[*i] = node->value;
	(*i)++;
	inOrderRBTree(tree, node->right, order, i);
}

void RBTransplant(Tree *tree, Node *tree1, Node *tree2)
{
	if (tree1->parent == tree->nil)
	{
		tree->root = tree2;
		tree2->parent = tree->nil;
		return;
	}

	tree2->parent = tree1->parent;
	if (tree1 == tree1->parent->left)	tree1->parent->left = tree2;
	else								tree1->parent->right = tree2;
}

Node *getRBNode(Tree *tree, Node *root, int value)
{
	if (root == tree->nil)	return tree->nil;
	if (root->value == value)	return root;
	Node *node = getRBNode(tree, root->left, value);
	if (node != tree->nil)	return node;
	node = getRBNode(tree, root->right, value);
	return node;
}

Node* RBMinimum(Tree *tree)
{
	Node *n = tree->root;
	if (n == tree->nil)	return tree->nil;
	while (n->left != tree->nil)		n = n->left;
	return n;
}

Node* RBMaximum(Tree *tree)
{
	Node *n = tree->root;
	if (n == tree->nil)	return tree->nil;
	while (n->right != tree->nil)	n = n->right;
	return n;
}




/*
* 以下是AVL树的操作
*/

Node* createAVLNode(int value);
int max(int a, int b);
int getHeight(Node *node);
void AVLInsertFixup(Tree *tree, Node *z);
void AVLDeleteFixup(Tree *tree, Node *z);
void AVLLeftRotate(Tree *tree, Node *x);
void AVLRightRotate(Tree *tree, Node *x);

Tree* initAVLTree()
{
	return initTree();
}

void destroyAVLTree(Tree *tree)
{
	destroyTree(tree);
}

void insertAVLTree(Tree *tree, int value)
{
	Node *node = createAVLNode(value);

	if (tree->root == NULL)
	{
		tree->root = node;
		return;
	}

	Node *n = tree->root;
	while (1)
	{
		n->size++;
		if (value < n->value)
		{
			if (n->left == NULL)
			{
				n->left = node;
				node->parent = n;
				break;
			}
			n = n->left;
		}
		else
		{
			if (n->right == NULL)
			{
				n->right = node;
				node->parent = n;
				break;
			}
			n = n->right;
		}
	}

	AVLInsertFixup(tree, node);
}

// 从插入的新节点开始向上更新树高并通过旋转结点保持平衡
void AVLInsertFixup(Tree *tree, Node *z)
{
	Node *tmp = z;

	while (z != NULL)
	{
		z->height = max(getHeight(z->left), getHeight(z->right)) + 1;

		if (z->parent != NULL && z->parent->parent != NULL)
		{
			Node *zp = z->parent;
			Node *zpp = zp->parent;
			zp->height = max(getHeight(zp->left), getHeight(zp->right)) + 1;
			zpp->height = max(getHeight(zpp->left), getHeight(zpp->right)) + 1;

			if (getHeight(zpp->left) - getHeight(zpp->right) == -2)
			{
				// 左旋zpp之前确保zp的右树高大于等于左树高
				if (getHeight(zp->left) > getHeight(zp->right))
				{
					AVLRightRotate(tree, zp);
				}
				AVLLeftRotate(tree, zpp);
			}
			else if (getHeight(zpp->left) - getHeight(zpp->right) == 2)
			{
				// 右旋zpp之前确保zp的左树高大于等于右树高
				if (getHeight(zp->left) < getHeight(zp->right))
				{
					AVLLeftRotate(tree, zp);
				}
				AVLRightRotate(tree, zpp);
			}
		}
		z = z->parent;
	}
}

void AVLLeftRotate(Tree *tree, Node *x)
{
	leftRotate(tree, x);
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	x->parent->height = x->height + 1;
	if (x->parent->parent != NULL)
	{
		x->parent->parent->height = max(getHeight(x->parent->parent->left), getHeight(x->parent->parent->right)) + 1;
	}
}

void AVLRightRotate(Tree *tree, Node *x)
{
	rightRotate(tree, x);
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	x->parent->height = x->height + 1;
	if (x->parent->parent != NULL)
	{
		x->parent->parent->height = max(getHeight(x->parent->parent->left), getHeight(x->parent->parent->right)) + 1;
	}
}

void deleteFromAVLTree(Tree *tree, Node *node)
{
	if (node == NULL)	return;

	Node *d = node->parent;

	Node *n = node;
	while (n->parent != NULL)
	{
		n = n->parent;
		n->size--;
	}

	if (node->left == NULL)
	{
		transplant(tree, node, node->right);
	}
	else if (node->right == NULL)
	{
		transplant(tree, node, node->left);
	}
	else
	{
		Tree t;
		t.root = node->right;
		Node *min = minimum(&t);
		Node *end = min->right;
		min->size = node->size - 1;
		if (node == tree->root)	tree->root = min;

		if (node->right != min)
		{
			transplant(tree, min, min->right);
			min->right = node->right;
			node->right->parent = min;
			d = min->parent;
		}
		else
		{
			d = min;
		}
		min->left = node->left;
		node->left->parent = min;
		transplant(tree, node, min);

		n = min->right;
		while (n != end)
		{
			n->size--;
			n = n->left;
		}
	}

	AVLDeleteFixup(tree, d);
	free(node);
}

// 从实际被删除的结点的父结点(因为从该节点开始树高有可能发生变化)出发，调整树高并通过旋转保持平衡
void AVLDeleteFixup(Tree *tree, Node *z)
{
	while (z != NULL)
	{
		z->height = max(getHeight(z->left), getHeight(z->right)) + 1;

		if (getHeight(z->left) - getHeight(z->right) == -2)
		{
			Node *zr = z->right;
			if (getHeight(zr->left) > getHeight(zr->right))
			{
				AVLRightRotate(tree, zr);
			}
			AVLLeftRotate(tree, z);
		}
		else if (getHeight(z->left) - getHeight(z->right) == 2)
		{
			Node *zl = z->left;
			if (getHeight(zl->left) < getHeight(zl->right))
			{
				AVLLeftRotate(tree, zl);
			}
			AVLRightRotate(tree, z);
		}

		z = z->parent;
	}
}

void deleteFromAVLTree(Tree *tree, int value)
{
	Node *node = getNode(tree->root, value);
	deleteFromAVLTree(tree, node);
}

Node* createAVLNode(int value)
{
	Node *node = createNode(value);
	node->height = 0;
	return node;
}

int max(int a, int b)
{
	if (a > b)	return a;
	return b;
}

int getHeight(Node *node)
{
	if (node == NULL)	return -1;
	return node->height;
}





/**
* 以下是Huffman Code的操作
*/

Node* min(Node **arr, int *used, int num);

Tree* HuffmanTree(char *collection, int *frequency, int num)
{
	int *used = (int *)malloc(sizeof(int)* num * 2);
	Node *arr[100];
	int i;
	int nodeNumber = num;
	Tree *tree = initTree();

	for (i = 0; i < num * 2; i++)
	{
		used[i] = 0;
		arr[i] = createNode(frequency[i]);
		arr[i]->name = collection[i];
	}
	Node *node;
	for (i = 0; i < num - 1; i++)
	{
		node = (Node *)malloc(sizeof(Node));
		Node *left = min(arr, used, nodeNumber);
		Node *right = min(arr, used, nodeNumber);
		node->left = left;
		node->right = right;
		node->value = left->value + right->value;
		arr[nodeNumber] = node;
		nodeNumber++;
	}
	tree->root = node;

	free(used);
	return tree;
}

char HuffmanDecode(Tree *tree, char *code)
{
	Node *n = tree->root;
	while (*code != '\0' && n != NULL)
	{
		int dir = *code - '0';
		if (dir == 0)
		{
			n = n->left;
		}
		else if (dir == 1)
		{
			n = n->right;
		}
		code++;
	}
	return n->name;
}

Node* min(Node *arr[], int *used, int num)
{
	int i, min = INT_MAX, k;
	for (i = 0; i < num; i++)
	{
		if (min > arr[i]->value && used[i] == 0)
		{
			min = arr[i]->value;
			k = i;
		}
	}
	used[k] = 1;
	return arr[k];
}
