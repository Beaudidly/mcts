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
    node->move = new_move;

    return node;
}

// TODO
mcts_node_s*
add_child(mcts_node_s* parent, node_queue_s* moves_list, uint8_t new_lplayer) {

}
