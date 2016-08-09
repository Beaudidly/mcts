#include "takeaway_state.h"
#include "mcts_state.h"
#include <stdio.h>

State_s*
createTakeState(uint8_t numPennies, uint8_t firstPlayer) {
    State_s* state = (State_s*) malloc(sizeof(State_s));
    state->position= malloc(sizeof(uint8_t));

    *((uint8_t*)state->position) = numPennies;

    // as first player is 1 or 2, this flips it
    state->lplayer = 3 - firstPlayer;

    // Add callback functions to the struct
    
    state->getMoves = getMovesList;
    state->doMove = performMove;
    state->gameResult = gameResult;
    state->getDeepCopy = deepCopy;

    return state;
}

void
destructTakeState(State_s* target) {
    if(target != NULL) {
        if(target->position != NULL) {
            free(target->position);
        }
        free(target);
    }
}

State_s*
deepCopy(State_s* target) {
    State_s* copy = (State_s*) malloc(sizeof(State_s));
    copy->position = malloc(sizeof(uint8_t)); 

    // need to derefernce the pointer to set and get the values
    *((uint8_t*)copy->position) = *((uint8_t*)target->position);
    copy->lplayer = target->lplayer;

     return copy;
}

uint8_t
currentPos(State_s* state) {
    return *((uint8_t*) state->position);
}

void
performMove(State_s* state, void* move) {
    *((uint8_t*)state->position) -= *((uint8_t*)move);

    // simple player toggle
    state->lplayer = 3 - state->lplayer;
}

NodeQueue_s*
getMovesList(State_s* state) {
    uint8_t pennies = *((uint8_t*)state->position);
    uint8_t ceiling = (pennies < 3) ? pennies : 3;

    NodeQueue_s* movesList = constructQueue();

    for(uint8_t i = 1; i <= ceiling; i++) {
        // The move has to be dynamically allocated
        uint8_t* tmpMove = (uint8_t*) malloc(sizeof(uint8_t));
        *tmpMove = i;

        enqueue(movesList, (void*) tmpMove);
    }

    return movesList;
}

int8_t
gameResult(State_s* state, uint8_t player) {
    uint8_t pennies = *((uint8_t*)state->position);

    if(pennies == 0) {
        if(state->lplayer == player) {
            return 0;
        } else {
            return 1;
        }
    } else {
        // Only for debugging purposes
        fprintf(stderr, "Logic error, gameResult called when game isn't \
                finished\n");
        exit(EXIT_FAILURE);
    }
}
