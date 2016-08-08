#include "takeaway_state.h"
#include <stdio.h>

TakeState_s*
createTakeState(uint8_t numPennies, uint8_t firstPlayer) {
    TakeState_s* state = (TakeState_s*) malloc(sizeof(TakeState_s));
    state->pennies = numPennies;

    // as first player is 1 or 2, this flips it
    state->lplayer = 3 - firstPlayer;

    return state;
}

void
destructTakeState(TakeState_s* target) {
    if(target != NULL) {
        free(target);
    }
}

TakeState_s*
deepCopy(TakeState_s* target) {
    TakeState_s* copy = (TakeState_s*) malloc(sizeof(TakeState_s));
    
    // deep copy isn't really complicated as there are no pointers
    copy->pennies = target->pennies;
    copy->lplayer = target->lplayer;

     return copy;
}

void
performMove(TakeState_s* state, uint8_t* move) {
    state->pennies -= *move;

    // simple player toggle
    state->lplayer = 3 - state->lplayer;
}

NodeQueue_s*
getMovesList(TakeState_s* state) {
    uint8_t ceiling = (state->pennies < 3) ? state->pennies : 3;

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
gameResult(TakeState_s* state, uint8_t player) {
    if(state->pennies == 0) {
        if(state->lplayer == player) {
            return 0;
        } else {
            return 1;
        }
    } else {
        fprintf(stderr, "Logic error, gameResult called when game isn't \
                finished\n");
        return NULL;
    }
}
