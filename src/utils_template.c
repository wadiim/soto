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

#endif // SOTO_TYPE
