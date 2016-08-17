#include "mcts.h"
#include "mcts_node.h"
#include "node_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/timeb.h>   // Posix solution, windows will have issues

static MctsNode_s*
select(const MctsNode_s* const root, const double c);

static double
UCT(const MctsNode_s* const node, const uint64_t rootPlays, const double c);
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

    // Run while the elapsed time has not surpassed the specified duration of 
    // milliseconds
    while( elapsed < duration ) {
        
        MctsNode_s* currNode = root;
        State_s* currState = state->getDeepCopy(state);

        // SELECTION
        // Traverse Nodes that have all their children generated
        while(isempty(currNode->rmoves) && !isempty(currNode->children)) {
            // Call UCT formula to select best child
            currNode = select(currNode, c);

            // Perform the move on the currState
            currState->doMove(currState, currNode->move);
        }

        // EXPANSION
        if(!isempty(currNode->rmoves)) {
            // Create and add a new child node to the current node
            // Pick a random move from the remaining moves
            // Perform the move on the current state
            // Update currNode to point to the new Child node

            currNode = addChild(currNode, currState);
        }

        // SIMULATION
        // Play out a random game from the new expanded node
        while(!isempty(currState->getMoves(currState))) {
            void* tmpMove = randRemove(currState->getMoves(currState));

            // Perform the random move on the current state
            currState->doMove(currState, tmpMove);
        }

        // BACKPROPAGATION
        int32_t score = currState->gameResult(currState, currNode->lplayer);
        backpropagation(score, currNode);
        
        
        // Update the elapsed time
        ftime(&check);
        elapsed = ((check.time - start.time) * (int64_t)1000)  +\
                  (check.millitm - start.millitm);
    }

    // choose the best move out of the root's children
    MctsNode_s* cursor = dequeue(root->children);
    MctsNode_s* max = cursor;

    cursor = dequeue(root->children);

    // Iterate through the remaining children to find the child with the
    // greatest number of plays (most exploited/explored from)
    while(cursor != NULL) {
        if(cursor->plays > max-> plays) {
            max = cursor;
        }

        cursor = dequeue(root->children);
    } 

    // DEBUG
    printf("\nTime Elapsed: %ld\n", elapsed);
    printf("Plays: %u\n", root->plays);

    // Return the move of the child node with the most plays as the best move
    return max->move;
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

    // favored will point to the child to be explored next
    Node_s* cursor = root->children->head;

    MctsNode_s* favored = cursor->data;
    double favWeight = UCT(favored, t, c);

    // iterate over remaining children to check if they have higher weights than the first
    cursor = cursor->next;
    while(cursor != NULL) {
        double weight = UCT(cursor->data, t, c);
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
    double right = c * pow(log((double) rootPlays) / (double) node->plays, 0.5);

    return left + right;
}
