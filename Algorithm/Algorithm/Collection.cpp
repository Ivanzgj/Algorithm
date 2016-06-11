#include "Collection.h"

Set *initSet(int setName)
{
	Set *set = (Set *)malloc(sizeof(Set));
	set->member = setName;
	set->p = NULL;
	return set;
}

Set *insert(Set *set, int member)
{
	Set *s = (Set *)malloc(sizeof(Set));
	s->member = member;
	s->p = set;
	return s;
}

Set *findSet(Set *member)
{
	if (member->p != NULL)
	{
		member->p = findSet(member->p);
	}
	return member;
}

Set *remove(Set *set)
{
	Set *ret = set->p;
	if (ret != NULL)
	{
		set->p = NULL;
	}
	return ret;
}

int isEmpty(Set *set)
{
	return set->p == NULL;
}
