#include <stdint.h>
#include "node_queue.h"
#include "mcts_node.h"

// TODO convert to camelCase

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
    node->children = construct_queue();
    node->move = new_move;

    return node;
}

mcts_node_s*
add_child(mcts_node_s* parent, childMovesGen_f func) {
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

    // adds the child to the parent's child list
    enqueue(parent->children,(void*) child);

    return child;
}

void
destruct_mcts_tree(mcts_node_s* root) {
    if(root == NULL ) return;
    
    mcts_node_s* child;

    while( (child = dequeue(root->children)) != NULL ) {
        destruct_mcts_tree(child);
    }
    // Destrroy the moves list, really hope you didn't copy pointers
    free_queue_data(root->rmoves); 

    destruct_node_queue(root->rmoves);
    destruct_node_queue(root->children);
    free(root->move); 
    free(root);
}

void
backpropagate(uint32_t game_result, mcts_node_s* node) {
    mcts_node_s* cursor = node;

    // Until the cursor reaches the Null stopper on the ultimate root,
    // increment the total playcount and add the score to the win counter
    // to each node on the path.
    while (cursor != NULL) {
        node->wins += game_result;
        node->plays++;
        cursor = cursor->parent;
    }
}
