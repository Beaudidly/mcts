#include "munit.h"
#include "mcts_state.h"
#include "takeaway_state.h"
#include "node_queue.h"
#include <stdint.h>

/**
 * Collection of unit tests for mcts_state.c
 * Using the Munit unit testing framework
 *
 * This batch of unit tests will be testing the functionality
 * of the pointers to functions within the State_s struct
 */

// TESTS

// MOVES
static MunitResult
movesTest(const MunitParameter params[], void* data) {
    State_s* state = createTakeState(20, 2);

    NodeQueue_s* list = state->getMoves(state);

    munit_assert_uint8(*((uint8_t*)dequeue(list)), ==, 1);
    munit_assert_uint8(*((uint8_t*)dequeue(list)), ==, 2);
    munit_assert_uint8(*((uint8_t*)dequeue(list)), ==, 3);

    destructTakeState(state);
    destructNodeQueue(list);

    return MUNIT_OK;
}

// DO MOVE
static MunitResult
doMovesTest(const MunitParameter params[], void* data) {
    State_s* state = createTakeState(20, 2);
    uint8_t* a = malloc(sizeof(uint8_t));
    uint8_t* b = malloc(sizeof(uint8_t));
    uint8_t* c = malloc(sizeof(uint8_t));

    *a = 3;
    *b = 2;
    *c = 1;

    state->doMove(state, (void*) a);
    munit_assert_uint8(currentPos(state), ==, 17);

    state->doMove(state, (void*) b);
    munit_assert_uint8(currentPos(state), ==, 15);

    state->doMove(state, (void*) c);
    munit_assert_uint8(currentPos(state), ==, 14);


    free(a);
    free(b);
    free(c);
    destructTakeState(state);

    return MUNIT_OK;
}

// GAME RESULT
static MunitResult
resultTest(const MunitParameter params[], void* data) {
    State_s* x = createTakeState(0, 1);
    State_s* y = createTakeState(0, 2);

    int8_t a = x->gameResult(x, 1);
    int8_t b = x->gameResult(x, 2);
    munit_assert_int8(a, ==, 1);
    munit_assert_int8(b, ==, 0);

    int8_t c = y->gameResult(y, 1);
    int8_t d = y->gameResult(y, 2);
    munit_assert_int8(c, ==, 0);
    munit_assert_int8(d, ==, 1);

    destructTakeState(x);
    destructTakeState(y);

    return MUNIT_OK;
}

// DEEP COPY
static MunitResult
deepTest(const MunitParameter params[], void* data) {
    State_s* init = createTakeState(20, 2);
    State_s* copy = init->getDeepCopy(init);

    // Ensure values are consistent
    munit_assert_uint8(currentPos(init), ==, currentPos(copy));
    munit_assert_uint8(init->lplayer, ==, copy->lplayer);

    // Ensure addresses are all different
    munit_assert_ptr(init, !=, copy);
    munit_assert_ptr(init->position, !=, copy->position);
    munit_assert_ptr(&(init->lplayer), !=, &(copy->lplayer));

    destructTakeState(init);
    destructTakeState(copy);

    return MUNIT_OK;
}

// SUITE STUFF
static MunitTest test_suite_tests[] = {
    { "/state/moves/", movesTest, NULL, NULL, 0, NULL },
    { "/state/domove/", doMovesTest, NULL, NULL, 0, NULL },
    { "/state/result/", resultTest, NULL, NULL, 0, NULL },
    { "/state/deep/", deepTest, NULL, NULL, 0, NULL },
    { NULL, NULL, NULL, NULL, 0, NULL }
};

static const MunitSuite test_suite = {
    (char*) "statesuite",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, (void*) "muhunit", argc, argv);
}
