#ifndef __NODE_QUEUE_H__
#define __NODE_QUEUE_H__

#include "mcts_node.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node_s {
   void* data;
   struct Node_s* next;
} Node_s;

typedef struct NodeQueue_s {
    Node_s* head;
    Node_s* tail;
    uint32_t elements;
} NodeQueue_s;

/**
 * Allocate an empty NodeQueue_s
 * head and tail defaulted to NULL
 * @return empty NodeQueue_s
 */
NodeQueue_s* constructQueue();

/**
 * Iterates through the queue freeing all of it's existign nodes
 * and then lastly frees the queue struct
 * @param queue the queue to be freed
 * @pre queue is not null
 */
void destructNodeQueue(NodeQueue_s* queue);

/**
 * Iterates through the queue's nodes freeing the data members
 *
 * @param queue to free the node data from
 * @pre all the node's have manually allocated data
 */
void freeQueueData(NodeQueue_s* queue);

/**
 * Create a new node from the data and add it to the queue
 *
 * @param queue the queue to add the new node to
 * @param newData the data to create the new node from
 * @pre the queue or node aren't NULL
 */
void enqueue(NodeQueue_s* queue, void* newData);

/**
 * Retrieves and removes the head of the queue
 * @param queue the queue to dequeue the first element
 */
void* dequeue(NodeQueue_s* queue);

/**
 * Returns pointer to the head of the queue without removing
 * the head node
 * @param queue the queue to peek at the head node of
 */
void* peek(NodeQueue_s* queue);

/**
 * Removes a random node from the list
 * @param the queue to remove a random node from
 * @return a Node_s* that was removed
 */
void* randRemove(NodeQueue_s* queue);

/**
 * Boolean check of whether the queue is empty or not.
 *     0 if not empty
 *     1 if empty
 * @param queue to check the empty status of
 * @return uint8_t 0 or 1 verifyign the empty status
 */
uint8_t isempty(NodeQueue_s* queue);

#endif
