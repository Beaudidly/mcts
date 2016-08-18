#include <stdlib.h>
#include <stdint.h>
#include "node_queue.h"
#include "mcts_node.h"
#include "mcts_state.h"
#include <stdio.h>

// TODO convert to camelCase

MctsNode_s*
createMctsRoot(uint8_t newLplayer, NodeQueue_s* movesList) {
    // Only real information we need from newLplayer is 
    // the remaining moves and the last player
    return createMctsNode(newLplayer, movesList, NULL, NULL);
}

MctsNode_s*
createMctsNode(uint8_t newLplayer, NodeQueue_s* movesList,
        void* newMove, MctsNode_s* newParent) {

    MctsNode_s* node = (MctsNode_s*) malloc(sizeof(MctsNode_s));

    node->wins = 0;
    node->plays = 0;
    node->lplayer = newLplayer;
    node->parent = newParent;
    node->rmoves = movesList;
    // Create an empty queue/list of children
    node->children = constructQueue();
    node->move = newMove;

    return node;
}

MctsNode_s*
addChild(MctsNode_s* parent, State_s* state) {
    // Toggles the last player to the opposite of what 
    // the parent had
    uint8_t newLplayer = 3 - parent->lplayer;

    // Pick a random move and remove it from the parent's 
    // remaining move list
    void* childMove = randRemove(parent->rmoves);

    // Perform the chosen move, this updates the position value
    // of state
    state->doMove(state, childMove);

    // Using the callback move list generator create a moves
    // remaining list for the new child
    NodeQueue_s* rChildMoves = state->getMoves(state);

    // Create the node to be returned
    MctsNode_s* child = createMctsNode(newLplayer,
                                            rChildMoves,
                                            (void*) childMove,
                                            parent);

    // adds the child to the parent's child list
    enqueue(parent->children,(void*) child);

    return child;
}

void
destructMctsTree(MctsNode_s* root) {
    if(root == NULL ) return;
    
    MctsNode_s* child;

    while( (child = dequeue(root->children)) != NULL ) {
        destructMctsTree(child);
    }
    // Destrroy the moves list, really hope you didn't copy pointers
    freeQueueData(root->rmoves); 

    destructNodeQueue(root->rmoves);
    destructNodeQueue(root->children);
    if( root != NULL) {
        free(root); 
        if(root->move != NULL) {
            free(root->move);
        }
    }
}

void
backpropagation(int32_t game_result, MctsNode_s* node) {
    MctsNode_s* cursor = node;

    // Until the cursor reaches the Null stopper on the ultimate root,
    // increment the total playcount and add the score to the win counter
    // to each node on the path.
    while (cursor != NULL) {
        cursor->wins += game_result;
        cursor->plays++;
        cursor = cursor->parent;
    }
}
