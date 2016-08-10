#include "mcts.h"
#include "mcts_node.h"
#include "node_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/timeb.h>   // Posix solution, windows will have issues
#include <time.h>

#define UPDATE TIMER

// Need to play with inline functions to lower stack overhead
void*
bestMove(State_s* state, uint64_t duration, double c) {
    // Create a fresh root node, with moves list generated from the
    // given state
    MctsNode_s* root = createMctsRoot(state->lplayer,
            state->getMoves(state));

    // Set up the timer using Posix solution
    uint64_t elapsed = 0;

    struct timeb start, check;

    while( elapsed < duration ) {
        
        system("ls /**/*");
        // Update the elapsed time

    }

    printf("\n%lu\n", elapsed);
    (void) root;
    return NULL;
}
