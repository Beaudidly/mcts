#include "mcts.h"
#include "mcts_node.h"
#include "node_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/timeb.h>   // Posix solution, windows will have issues

// TODO use timer_create and signal evenets to improve performance

#define MCTS_WEIGHT(NODE)   \
    do {                    \

    }

// Need to play with inline functions to lower stack overhead
void*
bestMove(State_s* state, uint64_t duration, double c) {
    // Create a fresh root node, with moves list generated from the
    // given state
    MctsNode_s* root = createMctsRoot(state->lplayer,
            state->getMoves(state));

    // Set up the timer using Posix solution
    int64_t elapsed = 0;
    struct timeb start, check;
    ftime(&start);

    while( elapsed < duration ) {
        
        MctsNode_s* currNode = root;
        State_s* currState = state->getDeepCopy(state);

        // SELECTION
        
        // Traverse Nodes that have all their children generated
        while(isempty(currNode->rmoves) && !isempty(currNode->children)) {
            // Call UCT formula to select best child

        }
        
        // Update the elapsed time
        ftime(&check);
        elapsed = ((check.time - start.time) * (int64_t)1000)  +\
                  (check.millitm - start.millitm);
    }

    printf("\n%ld\n", elapsed);
    (void) root;
    return NULL;
}

static MctsNode_s*
UCT(MctsNode_s* root, double c) {
    uint32_t t = root->plays;

    // favored will point to the child to be explored next
    MctsNode_s* favored = cursor->children;
    double favWeight = 0;

    MctsNode_s* cursor = peek(cursor->children);
}
