#ifndef __MCTS_H__
#define __MCTS_H__

#include "mcts_state.h"

/**
 * Using the 4 cycles of the Monte Carlo tree search:
 * 1) Selection
 * 2) Expansion
 * 3) Simulation
 * 4) backpropagation
 * bestMove returns the most visited move.
 *
 * @param currState the current state to calculate the best move to make
 * @param duration the number of milliseconds to spend on the calculation
 * @param c the exploration parameter in the UCT
 * @return a pointer to the calculated best move
 */
void*
bestMove(State_s* currState, uint64_t duration, double c);


#endif
