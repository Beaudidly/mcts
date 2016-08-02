#ifndef __NODE_QUEUE_H__
#define __NODE_QUEUE_H__

#include <"mcts_node.h">
#include <stdint.h>

#typedef struct node_queue_s {
    node_s* head;
    node_s* tail;
} node_queue_s;

#typedef struct node_s {
   mcts_node_s* data;
   node_s* next;
} node_s;

node_queue_s* construct();
void destruct(node_queue_s* queue);
void enqueue(node_queue_s* queue, node_s* node);
node_s* dequeue(node_queue_s* queue);
node_s* peek(node_queue_s* queue);
uint8_t isempty(node_queue_s* queue);

#endif
