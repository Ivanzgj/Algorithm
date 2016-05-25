#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

typedef struct Stack {
	int value;
	struct Stack *pre;
} Stack;

Stack* initStack();
void push(Stack **s, int value);
int pop(Stack **s);
int isEmpty(Stack *s);
void destroyStack(Stack **s);

#endif