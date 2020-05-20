#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stdbool.h>

void SOTO_TEMPLATE(swap,SOTO_TYPE)(SOTO_TYPE *x, SOTO_TYPE *y)
{
	SOTO_TYPE tmp = *x;
	*x = *y;
	*y = tmp;
}

void SOTO_TEMPLATE(soto_bubble_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len)
{
	for (size_t i = 0; i < len-1; ++i)
	{
		bool swapped = false;
		for (size_t j = 0; j < len-1-i; ++j)
		{
			if (arr[j] > arr[j+1])
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

#endif // SOTO_TYPE
