#include "Search.h"

int Search::binary_search(uint64_t array[], int first, int last, uint64_t element)
{
	if (first > last)
	{
		return -1;
	}

	int index;

	int mid = (first + last) / 2;

	if (element == array[mid])
	{
		index = mid;
	}
	else
	{
		if (element < array[mid])
		{
			index = binary_search(array, first, mid - 1, element);
		}
		else
		{
			index = binary_search(array, mid + 1, last, element);
		}
	}

	return index;
}