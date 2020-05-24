#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stdbool.h>

bool SOTO_TEMPLATE(soto_less,SOTO_TYPE)(SOTO_TYPE x, SOTO_TYPE y)
{
	return x < y;
}

bool SOTO_TEMPLATE(soto_greater,SOTO_TYPE)(SOTO_TYPE x, SOTO_TYPE y)
{
	return x > y;
}

void SOTO_TEMPLATE(swap,SOTO_TYPE)(SOTO_TYPE *x, SOTO_TYPE *y)
{
	SOTO_TYPE tmp = *x;
	*x = *y;
	*y = tmp;
}

#endif // SOTO_TYPE
