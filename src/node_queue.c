#include <stdint.h>
#include "node_queue.h"
#include <time.h>

node_queue_s*
construct() {
    node_queue_s* queue = malloc(sizeof(node_queue_s));

    queue->head = NULL;
    queue->tail = NULL;
    queue->elements = 0;

    return queue;
}

void
destruct(node_queue_s* queue) {
    node_s* cursor = queue->head;

    while( cursor != NULL ) {
        node_s* tmp = cursor;
        cursor = cursor->next;
        free(tmp);
    }

    free(queue);
}

void
enqueue(node_queue_s* queue, node_s* node) {
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
        queue->elements += 1;
    } else {
        queue->tail->next = node;
        queue->tail = node;
        queue->elements += 1;
    }
}

void*
dequeue(node_queue_s* queue) {
    if( queue->head == NULL ){
        return NULL;
    }

    node_s* ret_node = queue->head;

    if( queue->head == queue->tail ){
    
        queue->tail = NULL;
    }

    queue->head = ret_node->next;

    queue->elements -= 1;

    return ret_node->data;
}

void*
peek(node_queue_s *queue) {
    return queue->head->data;
}

void*
rand_remove(node_queue_s* queue) {

    if(queue->elements == 0) {
        return NULL;
    } else if(queue->elements == 1){
        return dequeue(queue);
    }

    // at this point there is at least two elements in the list
    srand((unsigned int)time(NULL));    // set a seed for rand
    uint32_t index = rand() % queue->elements;

    if(index == 0) {
        return dequeue(queue);
    }

    node_s* precursor = queue->head;
    node_s* cursor = precursor->next;

    for(int i = 1; i < index; i++){
        //Advance the cursors
        precursor = cursor;
        cursor = cursor->next;
    }

    // remove the node and splice the list together
    precursor->next = cursor->next;
    queue->elements -= 1;
    return cursor->data;
}

uint8_t
isempty(node_queue_s* queue) {
    if ( (queue->head == NULL) &&  (queue->tail == NULL)) {
        return 1;
    } else {
        return 0;
    }
}
