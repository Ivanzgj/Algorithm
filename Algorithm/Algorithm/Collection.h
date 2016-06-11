#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <stdlib.h>

typedef struct Set
{
	int member;
	Set *p;
} Set;

Set *initSet(int setName);
Set *insert(Set *set, int member);
Set *findSet(Set *member);
Set *remove(Set *set);
int isEmpty(Set *set);

#endif