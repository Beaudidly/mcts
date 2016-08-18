#define TEST
#include "../src/mcts.h"
#include "../src/takeaway_state.h"
#include <stdio.h>
#include <stdint.h>

int main() {
    State_s* state = createTakeState(15, 1); 
    NodeQueue_s* moves = state->getMoves(state);

    printf("isempty? %u\n", isempty(moves));
    uint8_t move = *((uint8_t*)dequeue(moves));
    printf("%u\n", move);
    move = *((uint8_t*)dequeue(moves));
    printf("%u\n", move);
    move = *((uint8_t*)dequeue(moves));
    printf("%u\n", move);
    printf("isempty? %u\n", isempty(moves));

    void* mover = bestMove(state, 500, 2);

    printf("BEST: %u\n", *((uint8_t*)mover));
}
