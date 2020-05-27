#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stdbool.h>

#ifdef SOTO_STRING
#include <string.h>
#endif

bool SOTO_TEMPLATE(soto_less,SOTO_TYPE)(SOTO_TYPE x, SOTO_TYPE y)
{
#ifdef SOTO_STRING
	return strcmp(x, y) < 0;
#else
	return x < y;
#endif
}

bool SOTO_TEMPLATE(soto_greater,SOTO_TYPE)(SOTO_TYPE x, SOTO_TYPE y)
{
#ifdef SOTO_STRING
	return strcmp(x, y) > 0;
#else
	return x > y;
#endif
}

void SOTO_TEMPLATE(swap,SOTO_TYPE)(SOTO_TYPE *x, SOTO_TYPE *y)
{
	SOTO_TYPE tmp = *x;
	*x = *y;
	*y = tmp;
}

#endif // SOTO_TYPE
