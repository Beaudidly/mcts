#include "../src/mcts.h"
#include "../src/takeaway_state.h"
#include <stdio.h>
#include <stdint.h>

int main() {
    State_s* state = createTakeState(20, 1); 
    bestMove(state, 5000, 2);
}
