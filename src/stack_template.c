#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stdlib.h>

void SOTO_TEMPLATE(soto_stack_init,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack)
{
	stack->size = 0;
	stack->data = malloc(sizeof(SOTO_TYPE)*SOTO_STACK_ALLOC_SIZE);
	stack->capacity = SOTO_STACK_ALLOC_SIZE;
}

void SOTO_TEMPLATE(soto_stack_free,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack)
{
	free(stack->data);
}

bool SOTO_TEMPLATE(soto_stack_empty,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack)
{
	return (stack->size == 0);
}

SOTO_TYPE SOTO_TEMPLATE(soto_stack_top,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack)
{
	return stack->data[stack->size - 1];
}

void SOTO_TEMPLATE(soto_stack_push,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack, SOTO_TYPE val)
{
	if (stack->size >= stack->capacity)
	{
		stack->data =
			realloc(stack->data, sizeof(val)*stack->capacity*2);
		stack->capacity *= 2;
	}
	stack->data[stack->size] = val;
	++stack->size;
}

void SOTO_TEMPLATE(soto_stack_pop,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_stack,SOTO_TYPE) *stack)
{
	if (stack->size > 0)
	{
		--stack->size;
	}
}

#endif // SOTO_TYPE
