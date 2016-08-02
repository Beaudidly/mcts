#include <stdint.h>
#include <"node_queue.h">

node_queue_s*
contstruct() {
    node_queue_s* queue = malloc(sizeof(node_queue_s));

    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

// TODO
void
destruct(node_queue_s* queue) {

}

void
enqueue(node_queue_s* queue, node_s* node) {
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

node_s*
dequeue(node_queue_s* queue) {
    node_s* ret_node;
    
    if( queue->head == NULL ){
        return NULL;
    }

    ret_node = queue->head;

    queue->head = ret_node->next;

    return ret_node;
}

node_s*
peek(node_queue_s *queue) {
    return queue->head;
}

uint8_t
isempty(node_queue_s queue) {
    if ( (queue->head == NULL) &&  (queue->tail == NULL)) {
        return 1;
    } else {
        return 0;
    }
}
