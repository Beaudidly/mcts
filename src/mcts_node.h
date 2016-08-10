#ifndef __MCTS_NODE_H__
#define __MCTS_NODE_H__

#include <stdint.h>
#include "node_queue.h"
#include "mcts_state.h"

typedef struct NodeQueue_s NodeQueue_s;
typedef NodeQueue_s* (*childMovesGen_f)(State_s*);
typedef void (*doMove)(State_s* state, void* move);
typedef void (*destructMove_f)(void*);

typedef struct MctsNode_s {
    // total wins from this nodes subtree
    int32_t wins;
    // total plays from this nodes subtree
    uint32_t plays;
    // last player to have moved
    uint8_t lplayer;
    struct MctsNode_s* parent;
    // remaining moves left that can create children
    NodeQueue_s* rmoves;
    // move that caused the game to reach this state
    NodeQueue_s* children;
    void* move;
} MctsNode_s;

/**
 * Creates a new root node. parent and move set to NULL.
 *
 * @param newLplayer the last player to have moved
 * @param movesList the remaining moves the node can perform
 * @return a pointer to a new MctsNode_s root
 * @pre newLplayer is 0 or 1
 */
MctsNode_s*
createMctsRoot(uint8_t newLplayer, NodeQueue_s* movesList);

/**
 * Creates a new mcts node.  
 *
 * @param newLplayer the last player to have moved
 * @param movesList the list of moves the node has left to perform
 * @param newMove the move that caused the state of the node
 * @param newParent the node that created this node
 * @return a pointer to a new MctsNode_s
 * @pre newLplayer is 0 or 1
 */
MctsNode_s*
createMctsNode(uint8_t newLplayer, NodeQueue_s* movesList,
                void* newMove, MctsNode_s* newParent);
/**
 * Creates a new MCTS node from a remaining move and adds it to the parent.
 *
 * @param parent the parent node in which to add a new child
 * @param state used to perform the move on, and generate a new
 *        moves list from
 * @param childMovesGen a callback function pointer to generate and populate
 *        the moves list for the child.  
 * @param doMove the function that applies the given move to the given state
 * @return the child that was created and added to the parent's child list
 * @pre there are remaining moves in the parent node
 */
MctsNode_s*
addChild(MctsNode_s* parent, State_s* state,
        childMovesGen_f func, doMove moveFunc);

/**
 * Recursively destruct the mcts nodes from the root node
 *
 * @param root the root node to destruct it's subtree
 */
void
destructMctsTree(MctsNode_s* root);

/**
 * Recursively backpropagates up the tree adding the win value and always
 * increasing a node's play count by 1.  Halts when a NULL value for parent 
 * is reached.
 *
 * @param gameResult is the value to be added to the win value of the node.
 * @param node the node that was simulated from and to backpropagate from
 */
void
backpropagation(int32_t gameResult, MctsNode_s* node);

/**
 * Prints a display of the tree
 */
//void
//printTree();
#endif
