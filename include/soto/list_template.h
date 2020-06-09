#ifdef SOTO_TYPE

#include "soto/soto.h"
#include <stdbool.h>
#include <stddef.h>

/*
 * A doubly linked list node.
 */
typedef struct SOTO_TEMPLATE(list_node,SOTO_TYPE)
{
	SOTO_TYPE data;
	struct SOTO_TEMPLATE(list_node,SOTO_TYPE) *prev;
	struct SOTO_TEMPLATE(list_node,SOTO_TYPE) *next;
} SOTO_TEMPLATE(soto_list_node,SOTO_TYPE);

/*
 * A doubly linked list.
 */
typedef struct SOTO_TEMPLATE(list,SOTO_TYPE)
{
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *front;
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *back;
} SOTO_TEMPLATE(soto_list,SOTO_TYPE);

/*
 * Construct an empty list.
 */
SOTO_TEMPLATE(soto_list,SOTO_TYPE) * SOTO_TEMPLATE(
	soto_list_create,SOTO_TYPE)(void);

/*
 * Free an entire list.
 */
void SOTO_TEMPLATE(soto_list_free,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list);

/*
 * Check whether the list is empty.
 */
bool SOTO_TEMPLATE(soto_list_empty,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list);

/*
 * Get the number of nodes.
 */
size_t SOTO_TEMPLATE(soto_list_size,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list);

/*
 * Add a node with the specified value to the end.
 * Return -1 if the back pointer is NULL but the list is not empty, 0 otherwise.
 */
int SOTO_TEMPLATE(soto_list_push_back,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value);

/*
 * Insert a node with the specified value to the beginning.
 * Return -1 if the front pointer is NULL but the list is not empty,
 * 0 otherwise.
 */
int SOTO_TEMPLATE(soto_list_push_front,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value);

/*
 * Remove the last node.
 */
void SOTO_TEMPLATE(soto_list_pop_back,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list);

/*
 * Remove the first node.
 */
void SOTO_TEMPLATE(soto_list_pop_front,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list);

/*
 * Find the position of the node with the specified value.
 * Return -1 if no such node is found.
 * Nodes are indexed from zero.
 */
int SOTO_TEMPLATE(soto_list_find,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, SOTO_TYPE value);

/*
 * Get the node at the specified position.
 * Return NULL if the selected position is past the end of the list.
 */
SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) * SOTO_TEMPLATE(
	soto_list_node_at,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos);

/*
 * Get the value of the node at the specified position.
 * Runtime error occurs if the selected position is past the end of the list
 * or the list provided is empty.
 */
SOTO_TYPE SOTO_TEMPLATE(soto_list_at,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos);

/*
 * Insert a node with the specified value before the selected position.
 */
void SOTO_TEMPLATE(soto_list_insert,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos, SOTO_TYPE value);

/*
 * Remove the node from the selected position.
 */
void SOTO_TEMPLATE(soto_list_remove,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list, size_t pos);

/*
 * Swap nodes.
 */
void SOTO_TEMPLATE(soto_list_swap,SOTO_TYPE)(
	SOTO_TEMPLATE(soto_list,SOTO_TYPE) *list,
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node1,
	SOTO_TEMPLATE(soto_list_node,SOTO_TYPE) *node2);

#endif // SOTO_TYPE
