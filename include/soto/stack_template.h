#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct SOTO_TEMPLATE(soto_stack_,SOTO_TYPE)
{
	SOTO_TYPE *data;
	size_t size;
	size_t capacity;
} SOTO_TEMPLATE(soto_stack,SOTO_TYPE);

/*
 * Initialize the stack.
 */
void SOTO_TEMPLATE(soto_stack_init,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack);

/*
 * Free the stack.
 */
void SOTO_TEMPLATE(soto_stack_free,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack);

/*
 * Check whether the stack is empty.
 */
bool SOTO_TEMPLATE(soto_stack_empty,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack);

/*
 * Return the top element.
 */
SOTO_TYPE SOTO_TEMPLATE(soto_stack_top,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack);

/*
 * Insert element at the top.
 */
void SOTO_TEMPLATE(soto_stack_push,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack, SOTO_TYPE val);

/*
 * Remove the top element.
 */
void SOTO_TEMPLATE(soto_stack_pop,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack);

#endif // SOTO_TYPE
