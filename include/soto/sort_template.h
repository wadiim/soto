#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stddef.h>

void SOTO_TEMPLATE(soto_bubble_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len);
void SOTO_TEMPLATE(soto_selection_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len);
void SOTO_TEMPLATE(soto_insertion_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len);
void SOTO_TEMPLATE(soto_quick_sort,SOTO_TYPE)(SOTO_TYPE arr[], size_t len);

#endif // SOTO_TYPE
