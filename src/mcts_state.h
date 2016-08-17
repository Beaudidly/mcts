#ifndef __MCTS_STATE_H__
#define __MCTS_STATE_H__

#include "node_queue.h"
#include <stdint.h>

typedef struct State_s {
    uint8_t lplayer;    // Last player to have logically moved
    void* position;     // The game specific position 
    // function that returns a NodeQueue_s of the possible moves
    NodeQueue_s* (*getMoves)(struct State_s* state); 
    // function that alters the state based on the given move
    void (*doMove)(struct State_s* state, void* move);
    // function that returns the score of the game
    int32_t (*gameResult)(struct State_s* state, uint8_t player);
    //function that provides a deep copy of the struct
    struct State_s* (*getDeepCopy)(struct State_s *state);
} State_s;

#endif
