#include "DynamicProgramming.h"
#include <map>
using namespace std;

void cutRod(int length, int **result, int **gain)
{
	map<int, int> price;
	price.insert(pair<int, int>(1, 1));
	price.insert(pair<int, int>(2, 2));
	price.insert(pair<int, int>(3, 4));
	price.insert(pair<int, int>(4, 5));
	price.insert(pair<int, int>(5, 7));

	*result = (int *)malloc(sizeof(int)* (length + 1));
	*gain = (int *)malloc(sizeof(int)* (length + 1));
	(*result)[0] = 0;
	(*gain)[0] = 0;
	int size, i;
	int max, m, k;

	for (size = 1; size <= length; size++)
	{
		max = INT_MIN;
		for (i = 0; i < size; i++)
		{
			if (price.find(size - i) == price.end())	continue;
			m = price.find(size - i)->second + (*gain)[i];
			if (m > max)
			{
				max = m;
				k = i;
			}
		}
		(*result)[size] = k;
		(*gain)[size] = max;
	}
}