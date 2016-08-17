#ifndef __TAKEAWAY_STATE_H__
#define __TAKEAWAY_STATE_H__

#include <stdint.h>
#include "mcts_state.h"
#include <stdlib.h>
#include "node_queue.h"

#define LAST_MOVE_WIN 0   // player who moves last loses

/*
 * Takeaway is a game where the last person to take a penny
 * from the pile loses. A mplayer must take between 1-3 pennies
 * if it is their turn.
 */

/**
 * dynamically allocate a TakeState_s struct 
 *
 * @parma numPennies the number of pennies in the logical pile
 * @param firstPlayer the player desired to go first
 * @return dynamically allocated TakeState_s
 */
State_s*
createTakeState(uint8_t numPennies, uint8_t firstPlayer);

/**
 * Cleans up the given manually allocated TakeState_s
 *
 * @param target pointer to the TakeState_s to free up
 */
void
destructTakeState(State_s* target);

/**
 * Create a deep copy of the TakeState_s
 *
 * @param state the state to create a copy of
 * @return a new dynamically allocated deep copy of state
 */
State_s*
deepCopy(State_s* state);

/**
 * Perform the given move on the given state
 *
 * @param state the state to perform the move on
 * @param move the move to be performed on the state
 * @pre the move is legal and follows the rules of the game
 */
void
performMove(State_s* state, void* move);

/**
 * Generate a list of moves possible to perform from the given state.
 * The moves are dynamically allocated.
 *
 * @param state the TakeState_s to generate moves from
 * @return the NodeQueue_s of the states moves remaining to perform
 */
NodeQueue_s*
getMovesList(State_s* state);

/**
 * Provides the score/outcome of the game based on the state and
 * the last player to have moved in relativity to lPlayer.
 *
 * @param state the TakeState_s to judge the winner
 * @param player determines if the ending is a win or loss for them
 * @return int8_t score based on the outcome relative to player
 */
int32_t
gameResult(State_s* state, uint8_t player);

/** Return  the current position of the game
 *
 * @param state the gamestate to retrieve the position from
 * @return uin8_t quantity of the number of pennies left
 */
uint8_t
currentPos(State_s* state);
#endif
