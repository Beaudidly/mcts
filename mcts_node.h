#ifndef __MCTS_NODE_H__
#define __MCTS_NODE_H__

#include <stdint.h>

typedef struct mcts_node_s {
    uint32_t wins;                          // total wins from this nodes subtree
    uint32_t plays;                         // total plays from this nodes subtree
    uint8_t lplayer;                        // last player to have moved
    struct mcts_node_s* parent;             
    struct mcts_node_s* first_child;        // pointer to first child of the current node
    void* move;                             // move that caused the game to reach this state
} mcts_node_s;

// Creates a new root node.  parent and move set to NULL

/**
 * Creates a new root node. parent and move set to NULL.
 * @param new_lplayer the last player to have moved
 * @return a pointer to a new mcts_node_s
 */
mcts_node_s* create_mcts_node(uint8_t new_lplayer);

/**
 * Creates a new mcts node.  
 *
 * @param new_lplayer the last player to have moved
 * @param new_move the move to have caused the current state/position of the node
 * @param new_parent pointer to the parent node of the new node
 * @return a new mcts_node_s 
 */
mcts_node_s* create_mcts_node(void* state, void* new_move, mcts_node_s* new_parent);

/**
 * Recursively backpropagates up the tree adding the win value and always increasing a node's
 * play count by 1.  Halts when a NULL value for parent is reached.
 *
 * @param game_result is the value to be added to the win value of the node.
 */
void backpropagate(uint32_t game_result);

/**
 * Prints a display of the tree
 */
void print_tree();
#endif
