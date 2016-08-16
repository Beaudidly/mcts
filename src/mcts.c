#include "mcts.h"
#include "mcts_node.h"
#include "node_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/timeb.h>   // Posix solution, windows will have issues

// TODO use timer_create and signal evenets to improve performance

// Need to play with inline functions to lower stack overhead
void*
bestMove(State_s* state, const uint64_t duration, const double c) {
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

/**
 * Selects the child based on their weights according to the UCT algorithm
 *
 * @param root the root node to find the best child of
 * @param c the constant value to use for the UCT formula
 * @return pointer to the child with the highest UCT weight
 */
static MctsNode_s*
select(const MctsNode_s* const root, const double c) {

    // Consider using absolute root's play count
    uint32_t t = root->plays;
    NodeQueue_s* cursorList = root->children;

    // favored will point to the child to be explored next
    Node_s* cursor = cursorList->head;

    MctsNode_s* favored = cursor->data;
    double favWeight = UCT(favored, root->plays, c);

    // iterate over remaining children to check if they have higher weights than the first
    cursor = cursorList->next;
    while(cursor != NULL) {
        double weight = UCT(cursor->data, root->plays, c);
        if(weight > favWeight) {
            favored = cursor->data;
            favWeight = weight;
        }

        cursor = cursor->next;
    }
    
    // favored points to the mcts node with the highest exploration vs exploitation weight
    return favored;
}

/**
 * Get the double value of the weight of the node in respect to it's parent
 *
 * @param node a pointer to the node to get the weight of
 * @param c the double constant value to use for the UCT formula
 * @param rootPlays the number of total plays from the root
 * @return a double value of the weight of the node
 * @pre the node is not a root
 */
static double
UCT(const MctsNode_s* const node, const uint64_t rootPlays, const double c) {
    double left = (node->wins / (double) node->plays);

    // optimize through gcc exponentials
    double right = c * pow(log((double) rootPlays) / (double) node->plays);

    return left + right;
}
