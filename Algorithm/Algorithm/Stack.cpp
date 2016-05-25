#include "Stack.h"

Stack* initStack()
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->pre = NULL;
	return s;
}

void push(Stack **s, int value)
{
	Stack *n = (Stack *)malloc(sizeof(Stack));
	n->pre = *s;
	n->value = value;
	*s = n;
}

int pop(Stack **s)
{
	if ((*s)->pre == NULL)
	{
		return INT_MAX;
	}

	int value = (*s)->value;
	Stack *pre = (*s)->pre;
	free(*s);
	*s = pre;
	return value;
}

int isEmpty(Stack *s)
{
	if (s->pre == NULL)
	{
		return 1;
	}
	return 0;
}

void destroyStack(Stack **s)
{
	while (*s != NULL)
	{
		Stack *pre = (*s)->pre;
		free(*s);
		*s = pre;
	}
}
