#include "takeaway_state.h"
#include "mcts_state.h"
#include "node_queue.h"
#include <stdio.h>
#include <stdint.h>


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

        // Read user input into buffer, ()
        if(fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // validate that move is properly set
            if( 1 == sscanf(buffer, "%u", &move)) {
                // validate that the move is in range
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
    State_s* tmp = createTakeState(20, 2);
    uint8_t a = getInput(tmp);
    printf("%u\n", a);
}
#endif
