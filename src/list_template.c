#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef SOTO_STRING
#include <string.h>
#endif

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

void SOTO_TEMPLATE(soto_list_push_back,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value)
{
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
}

void SOTO_TEMPLATE(soto_list_push_front,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value)
{
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
}

void SOTO_TEMPLATE(soto_list_pop_back,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	if (SOTO_TEMPLATE(soto_list_empty,SOTO_TYPE)(list) == true)
	{
		return;
	}
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

void SOTO_TEMPLATE(soto_list_pop_front,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list)
{
	if (SOTO_TEMPLATE(soto_list_empty,SOTO_TYPE)(list) == true)
	{
		return;
	}
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

#endif // SOTO_TYPE
