#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stdbool.h>
#include <stdlib.h>

void SOTO_TEMPLATE(swap,SOTO_TYPE)(SOTO_TYPE *x, SOTO_TYPE *y)
{
	SOTO_TYPE tmp = *x;
	*x = *y;
	*y = tmp;
}

void SOTO_TEMPLATE(soto_bubble_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y))
{
	for (size_t i = 0; i < len-1; ++i)
	{
		bool swapped = false;
		for (size_t j = 0; j < len-1-i; ++j)
		{
			if ((*comp)(arr[j], arr[j+1]))
			{
				SOTO_TEMPLATE(swap,SOTO_TYPE)
					(&arr[j], &arr[j+1]);
				swapped = true;
			}
		}
		if (swapped == false)
		{
			break;
		}
	}
}

void SOTO_TEMPLATE(soto_selection_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y))
{
	for (size_t i = 0; i < len-1; ++i)
	{
		size_t min_idx = i;
		for (size_t j = i+1; j < len; ++j)
		{
			if ((*comp)(arr[min_idx], arr[j]))
			{
				min_idx = j;
			}
		}
		SOTO_TEMPLATE(swap,SOTO_TYPE)(&arr[min_idx], &arr[i]);
	}
}

void SOTO_TEMPLATE(soto_insertion_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y))
{
	for (size_t i = 1; i < len; ++i)
	{
		SOTO_TYPE key = arr[i];
		size_t j = i;
		while (j > 0 && (*comp)(arr[j-1], key))
		{
			arr[j] = arr[j-1];
			--j;
		}
		arr[j] = key;
	}
}

void SOTO_TEMPLATE(soto_quick_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y))
{
	if (len <= 1) return;
	SOTO_TYPE pivot = arr[0];
	SOTO_TYPE *arr1 = malloc((len-1)*sizeof(SOTO_TYPE));
	SOTO_TYPE *arr2 = malloc((len-1)*sizeof(SOTO_TYPE));
	size_t i, i1 = 0, i2 = 0;
	for (i = 1; i < len; ++i)
	{
		if ((*comp)(pivot, arr[i]))
		{
			arr1[i1++] = arr[i];
		}
		else
		{
			arr2[i2++] = arr[i];
		}
	}
	SOTO_TEMPLATE(soto_quick_sort,SOTO_TYPE)(arr1, i1, comp);
	SOTO_TEMPLATE(soto_quick_sort,SOTO_TYPE)(arr2, i2, comp);
	for (i = 0; i < i1; ++i)
	{
		arr[i] = arr1[i];
	}
	arr[i] = pivot;
	for (i = i1+1; i < len; ++i)
	{
		arr[i] = arr2[i-i1-1];
	}
	free(arr2);
	free(arr1);
}

#endif // SOTO_TYPE
