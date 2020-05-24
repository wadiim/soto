#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stddef.h>
#include <stdbool.h>

void SOTO_TEMPLATE(soto_bubble_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y));
void SOTO_TEMPLATE(soto_selection_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y));
void SOTO_TEMPLATE(soto_insertion_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y));
void SOTO_TEMPLATE(soto_quick_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len,
	bool (*comp)(SOTO_TYPE x, SOTO_TYPE y));

#endif // SOTO_TYPE
