#include <stdint.h>
#include "node_queue.h"
#include <time.h>

NodeQueue_s*
constructQueue() {
    NodeQueue_s* queue = malloc(sizeof(NodeQueue_s));

    queue->head = NULL;
    queue->tail = NULL;
    queue->elements = 0;

    return queue;
}

void
destructNodeQueue(NodeQueue_s* queue) {
    Node_s* cursor = queue->head;

    while( cursor != NULL ) {
        Node_s* tmp = cursor;
        cursor = cursor->next;
        if( tmp != NULL ) {
            free(tmp);
        }
    }

    free(queue);
}

void
freeQueueData(NodeQueue_s* queue) {
    Node_s* cursor = queue->head;

    while(cursor != NULL) {
        free(cursor->data);
        cursor = cursor->next;
    }
}

void
enqueue(NodeQueue_s* queue, void* newData) {
    Node_s* node = (Node_s*) malloc(sizeof(Node_s));
    node->data = newData;
    node->next = NULL;

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
dequeue(NodeQueue_s* queue) {
    if( queue->head == NULL ){
        return NULL;
    }

    Node_s* retNode = queue->head;
    void* retData = retNode->data;

    if( queue->head == queue->tail ){
    
        queue->tail = NULL;
    }

    // Advance the head of the queue
    queue->head = retNode->next;
    queue->elements -= 1;

    free(retNode);
    return retData;
}

void*
peek(NodeQueue_s *queue) {
    return queue->head->data;
}

void*
randRemove(NodeQueue_s* queue) {

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

    Node_s* precursor = queue->head;
    Node_s* cursor = precursor->next;

    for(int i = 1; i < index; i++){
        //Advance the cursors
        precursor = cursor;
        cursor = cursor->next;
    }

    // remove the node and splice the list together
    precursor->next = cursor->next;
    queue->elements -= 1;

    // If precursor is at the end, update the queue's tail
    if(precursor->next == NULL) {
        queue->tail = precursor;
    }

    // Node needs to be freed, so we temporarily store it's data
    void* retData = cursor->data;
    free(cursor);

    return retData;
}

uint8_t
isempty(NodeQueue_s* queue) {
    if ( (queue->head == NULL) &&  (queue->tail == NULL)) {
        return 1;
    } else {
        return 0;
    }
}
