#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef SOTO_STRING
#include <string.h>
#endif

static void SOTO_TEMPLATE(swap_node_ptr,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) **node1,
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) **node2)
{
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;
}

static bool SOTO_TEMPLATE(are_they_adjacent,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node1,
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node2)
{
	return (node1->next == node2 && node2->prev == node1 ||
		node2->next == node1 && node1->prev == node2);
}

SOTO_TEMPLATE(soto_list,SOTO_TYPE) * SOTO_TEMPLATE(
	soto_list_create,SOTO_TYPE)(void)
{
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list =
		malloc(sizeof(SOTO_TEMPLATE(soto_list,SOTO_TYPE)));
	list->front = list->back = NULL;
	return list;
}

void SOTO_TEMPLATE(soto_list_free,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *tmp;
	while (list->front != NULL)
	{
		tmp = list->front;
		list->front = list->front->next;
		free(tmp);
	}
}

bool SOTO_TEMPLATE(soto_list_empty,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	return (list->front == NULL && list->back == NULL) ? true : false;
}

size_t SOTO_TEMPLATE(soto_list_size,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	size_t size = 0;
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node = list->front;
	while (node != NULL)
	{
		++size;
		node = node->next;
	}
	return size;
}

int SOTO_TEMPLATE(soto_list_push_back,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value)
{
	if (list->front != NULL && list->back == NULL)
	{
		return -1;
	}
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node =
		malloc(sizeof(SOTO_TEMPLATE(soto_list_node,SOTO_TYPE)));
	node->data = value;
	node->next = NULL;
	node->prev = list->back;
	if (SOTO_TEMPLATE(soto_list_empty,SOTO_TYPE)(list))
	{
		list->front = list->back = node;
	}
	else
	{
		list->back->next = node;
		list->back = node;
	}
	return 0;
}

int SOTO_TEMPLATE(soto_list_push_front,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value)
{
	if (list->front == NULL && list->back != NULL)
	{
		return -1;
	}
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node =
		malloc(sizeof(SOTO_TEMPLATE(soto_list_node,SOTO_TYPE)));
	node->data = value;
	node->prev = NULL;
	node->next = list->front;
	if (SOTO_TEMPLATE(soto_list_empty,SOTO_TYPE)(list))
	{
		list->front = list->back = node;
	}
	else
	{
		list->front->prev = node;
		list->front = node;
	}
	return 0;
}

void SOTO_TEMPLATE(soto_list_pop_back,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	if (list->back != NULL)
	{
		SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *tmp = list->back;
		list->back = list->back->prev;
		if (list->back != NULL)
		{
			list->back->next = NULL;
		}
		else
		{
			list->front = NULL;
		}
		free(tmp);
	}
}

void SOTO_TEMPLATE(soto_list_pop_front,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	if (list->front != NULL)
	{
		SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *tmp = list->front;
		list->front = list->front->next;
		if (list->front != NULL)
		{
			list->front->prev = NULL;
		}
		else
		{
			list->back = NULL;
		}
		free(tmp);
	}
}

int SOTO_TEMPLATE(soto_list_find,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value)
{
	int retval = -1;
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node = list->front;
	for (int i = 0; node != NULL; ++i, node = node->next)
	{
#ifdef SOTO_STRING
		if (strcmp(node->data, value) == 0)
#else
		if (node->data == value)
#endif
		{
			retval = i;
			break;
		}
	}
	return retval;
}

SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) * SOTO_TEMPLATE(
	soto_list_node_at,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos)
{
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node = list->front;
	size_t i = 0;
	for (i; node != NULL && i < pos; ++i, node = node->next);
	return (i == pos) ? node : NULL;
}

SOTO_TYPE SOTO_TEMPLATE(soto_list_at,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos)
{
	// Allow for runtime error if 'soto_list_node_at' returns NULL.
	return SOTO_TEMPLATE(soto_list_node_at,SOTO_TYPE)(list, pos)->data;
}

void SOTO_TEMPLATE(soto_list_insert,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos, SOTO_TYPE value)
{
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node =
		SOTO_TEMPLATE(soto_list_node_at,SOTO_TYPE)(list, pos);
	if (node != NULL)
	{
		if (node->prev == NULL)
		{
			SOTO_TEMPLATE(soto_list_push_front,SOTO_TYPE)(
				list, value);
		}
		else
		{
			SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *new_node =
				malloc(sizeof(SOTO_TEMPLATE(
					soto_list_node,SOTO_TYPE)));
			new_node->data = value;
			new_node->next = node;
			new_node->prev = node->prev;
			node->prev->next = new_node;
			node->prev = new_node;
		}
	}
	else
	{
		SOTO_TEMPLATE(soto_list_push_back,SOTO_TYPE)(list, value);
	}
}

void SOTO_TEMPLATE(soto_list_remove,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos)
{
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node =
		SOTO_TEMPLATE(soto_list_node_at,SOTO_TYPE)(list, pos);
	if (node == NULL)
	{
		return;
	}
	else if (node->prev == NULL)
	{
		SOTO_TEMPLATE(soto_list_pop_front,SOTO_TYPE)(list);
	}
	else if (node->next == NULL)
	{
		SOTO_TEMPLATE(soto_list_pop_back,SOTO_TYPE)(list);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
	}
}

void SOTO_TEMPLATE(soto_list_swap,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list,
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node1,
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node2)
{
	if (node1 == NULL || node2 == NULL || node1 == node2)
	{
		return;
	}

	if (node2->next == node1)
	{
		SOTO_TEMPLATE(swap_node_ptr,SOTO_TYPE)(&node1, &node2);
	}

	if (node1->prev != NULL)
	{
		node1->prev->next = node2;
	}
	if (node2->next != NULL)
	{
		node2->next->prev = node1;
	}

	if (SOTO_TEMPLATE(are_they_adjacent,SOTO_TYPE)(node1, node2))
	{
		node1->next = node2->next;
		node2->prev = node1->prev;
		node1->prev = node2;
		node2->next = node1;
	}
	else
	{
		if (node1->next != NULL)
		{
			node1->next->prev = node2;
		}
		if (node2->prev != NULL)
		{
			node2->prev->next = node1;
		}

		SOTO_TEMPLATE(swap_node_ptr,SOTO_TYPE)(&node1->prev,
			&node2->prev);
		SOTO_TEMPLATE(swap_node_ptr,SOTO_TYPE)(&node1->next,
			&node2->next);
	}

	if (list->front == node1)
	{
		list->front = node2;
	}
	else if (list->front == node2)
	{
		list->front = node1;
	}
	if (list->back == node1)
	{
		list->back = node2;
	}
	else if (list->back == node2)
	{
		list->back = node1;
	}
}

#endif // SOTO_TYPE
