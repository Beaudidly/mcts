#include "takeaway_state.h"
#include "mcts_state.h"
#include "node_queue.h"
#include <stdint.h>
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
    uint8_t numPennies = *((uint8_t*)target->position);
    uint8_t firstPlayer = 3 - target->lplayer;

    // Using pass by value to ensure references aren't the same
    // Optimize to prevent function calling overhead
    State_s* copy = createTakeState(numPennies, firstPlayer);

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

int32_t
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

#ifndef _TEST_
static uint8_t
getInput(State_s* state) {
    // Temporary moves list to get min and max move from
    NodeQueue_s* moves = getMovesList(state);

    // Minimum and maximum values for picking a move from
    // queue is constructed with lowest elements at the head
    const uint8_t min = *((uint8_t*)moves->head->data);
    const uint8_t max = *((uint8_t*)moves->tail->data); 

    // Loop until the user picks a valid move
    for(;;) {
        // Print the move choices
        printf("Pick a move [");
        for(uint8_t i = min; i < max; i++) {
            printf("%u, ", i);
        }
        printf("%u]: ", max);

        char buffer[256];
        // 32 bytes to satisfy '%u' for sscanf.
        uint32_t move;
            printf("%u %u UGH\n", min, max);

        // Read user input into buffer, ()
        if(fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // validate that move is properly set
            printf("%u %u UGH\n", min, max);
            if( 1 == sscanf(buffer, "%u", &move)) {
                // validate that the move is in range
                printf("%u %u UGH\n", min, max);
                if((min <= move) && (move <= max)) {
                    return move;
                } else {
                    printf("Selected move is out of range.\n");
                }
            } else {
                printf("Move must be in range and an integer\n");
            }
        } else {
            fprintf(stderr, "Error getting input.\n");
        }

    }


    destructNodeQueue(moves);
}
int
main() {
}
#endif
