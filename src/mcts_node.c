#include <stdint.h>
#include "node_queue.h"
#include "mcts_node.h"

mcts_node_s*
create_mcts_root(uint8_t new_lplayer, node_queue_s* moves_list) {
    // Only real information we need from new_lplayer is 
    // the remaining moves and the last player
    return create_mcts_node(new_lplayer, moves_list, NULL, NULL);
}

mcts_node_s*
create_mcts_node(uint8_t new_lplayer, node_queue_s* moves_list,
        void* new_move, mcts_node_s* new_parent) {

    mcts_node_s* node = (mcts_node_s*) malloc(sizeof(mcts_node_s));

    node->wins = 0;
    node->plays = 0;
    node->lplayer = new_lplayer;
    node->parent = new_parent;
    node->rmoves = moves_list;
    // Create an empty queue/list of children
    node->children = construct();
    node->move = new_move;

    return node;
}

// TODO
mcts_node_s*
add_child(mcts_node_s* parent, node_queue_s* moves_list,
        childMovesGen_f func) {
    // Toggles the last player to the opposite of what 
    // the parent had
    uint8_t new_lplayer = 3 - parent->lplayer;

    // Pick a random move and remove it from the parent's 
    // remaining move list
    void* childMove = rand_remove(parent->rmoves);

    // Using the callback move list generator create a moves
    // remaining list for the new child
    node_queue_s* rChildMoves = func(childMove);

    // Create the node to be returned
    mcts_node_s* child = create_mcts_node(new_lplayer,
                                            rChildMoves,
                                            (void*) childMove,
                                            parent);

    enqueue(parent,(void*) child);

}
