#ifndef __TAKEAWAY_H__
#define __TAKEAWAY_H__

#include <stdin.h>
#include <stdlib.h>
#include "node_queue.h"

#define LAST_MOVE_WIN 0   // player who moves last loses

/*
 * Takeaway is a game where the last person to take a penny
 * from the pile loses. A mplayer must take between 1-3 pennies
 * if it is their turn.
 */

typedef struct TakeState_s {
    int8_t pennies;     // number of pennies in the pile
    uint8_t lplayer;    // last player to have played
}

/**
 * dynamically allocate a TakeState_s struct 
 *
 * @parma numPennies the number of pennies in the logical pile
 * @param firstPlayer the player desired to go first
 * @return dynamically allocated TakeState_s
 */
TakeState_s*
createTakeState(int8_t numPennies, uint8_t firstPlayer);

/**
 * Create a deep copy of the TakeState_s
 *
 * @param state the state to create a copy of
 * @return a new dynamically allocated deep copy of state
 */
TakeState_s*
deepCopy(TakeState_s* state);

/**
 * Perform the given move on the given state
 *
 * @param state the state to perform the move on
 * @param move the move to be performed on the state
 * @pre the move is legal and follows the rules of the game
 */
void
performMove(TakeState_s* state, int8_t* move);

/**
 * Generate a list of moves possible to perform from the given state.
 * The moves are dynamically allocated.
 *
 * @param state the TakeState_s to generate moves from
 * @return the NodeQueue_s of the states moves remaining to perform
 */
NodeQueue_s*
getMovesList(TakeState_s* state);

/**
 * Provides the score/outcome of the game based on the state and
 * the last player to have moved in relativity to lPlayer.
 *
 * @param state the TakeState_s to judge the winner
 * @param player determines if the ending is a win or loss for them
 * @return int8_t score based on the outcome relative to player
 */
int8_t
gameResult(TakeState_s* state, uint8_t player);

/**
 * Get a move selection from a human player
 *
 * @param state the TakeState_s to get legal moves from
 * @return int8_t move selected by the human player
 */
int8_t
humanMoveInput(TakeState_s* state);

/**
 * returns string form of TakeState_s
 * @param state TakeState_s to get a string form of
 * @return char* string of the TakeState_s
 */
char*
toString(TakeState_s* state);

#endif
