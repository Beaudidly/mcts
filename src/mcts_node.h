#ifndef __MCTS_NODE_H__
#define __MCTS_NODE_H__

#include <stdint.h>
#include "node_queue.h"

typedef struct node_queue_s node_queue_s;
typedef node_queue_s* (*childMovesGen_f)(void*);
typedef void (*destructMove_f)(void*);

typedef struct mcts_node_s {
    // total wins from this nodes subtree
    uint32_t wins;
    // total plays from this nodes subtree
    uint32_t plays;
    // last player to have moved
    uint8_t lplayer;
    struct mcts_node_s* parent;
    // remaining moves left that can create children
    node_queue_s* rmoves;
    // move that caused the game to reach this state
    node_queue_s* children;
    void* move;
} mcts_node_s;

/**
 * Creates a new root node. parent and move set to NULL.
 * @param new_lplayer the last player to have moved
 * @param moves_list the remaining moves the node can perform
 * @return a pointer to a new mcts_node_s root
 * @pre new_lplayer is 0 or 1
 */
mcts_node_s*
create_mcts_root(uint8_t new_lplayer, node_queue_s* moves_list);

/**
 * Creates a new mcts node.  
 *
 * @param new_lplayer the last player to have moved
 * @param moves_list the list of moves the node has left to perform
 * @param new_move the move that caused the state of the node
 * @param new_parent the node that created this node
 * @return a pointer to a new mcts_node_s
 * @pre new_lplayer is 0 or 1
 */
mcts_node_s*
create_mcts_node(uint8_t new_lplayer, node_queue_s* moves_list,
                void* new_move, mcts_node_s* new_parent);
/**
 * Creates a new MCTS node from a remaining move and adds it to the parent.
 *
 * @param parent the parent node in which to add a new child
 * @param childMovesGen a callback function pointer to generate and populate
 *        the moves list for the child.  
 * @return the child that was created and added to the parent's child list
 * @pre there are remaining moves in the parent node
 */
mcts_node_s*
add_child(mcts_node_s* parent, childMovesGen_f func);

/**
 * Recursively destruct the mcts nodes from the root node
 *
 * @param root the root node to destruct it's subtree
 */
void
destruct_mcts_tree(mcts_node_s* root);

/**
 * Recursively backpropagates up the tree adding the win value and always increasing a node's
 * play count by 1.  Halts when a NULL value for parent is reached.
 *
 * @param game_result is the value to be added to the win value of the node.
 * @param node the node that was simulated from and to backpropagate from
 */
void
backpropagate(uint32_t game_result, mcts_node_s* node);

/**
 * Prints a display of the tree
 */
//void
//print_tree();
#endif
