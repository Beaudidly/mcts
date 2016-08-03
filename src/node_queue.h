#ifndef __NODE_QUEUE_H__
#define __NODE_QUEUE_H__

#include "mcts_node.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct node_s {
   mcts_node_s* data;
   struct node_s* next;
} node_s;

typedef struct node_queue_s {
    node_s* head;
    node_s* tail;
} node_queue_s;

/**
 * Allocate an empty node_queue_s
 * head and tail defaulted to NULL
 * @return empty node_queue_s
 */
node_queue_s* construct();

/**
 * Iterates through the queue freeing all of it's existign nodes
 * and then lastly frees the queue struct
 * @param queue the queue to be freed
 * @pre queue is not null
 */
void destruct(node_queue_s* queue);

/**
 * Add the node to the end or tail of the queue
 * @param node the node to be added to the queue
 * @pre the queue or node aren't NULL
 */
void enqueue(node_queue_s* queue, node_s* node);

/**
 * Retrieves and removes the head of the queue
 * @param queue the queue to dequeue the first element
 */
node_s* dequeue(node_queue_s* queue);

/**
 * Returns pointer to the head of the queue without removing
 * the head node
 * @param queue the queue to peek at the head node of
 */
node_s* peek(node_queue_s* queue);

/**
 * Boolean check of whether the queue is empty or not.
 *     0 if not empty
 *     1 if empty
 * @param queue to check the empty status of
 * @return uint8_t 0 or 1 verifyign the empty status
 */
uint8_t isempty(node_queue_s* queue);

#endif
