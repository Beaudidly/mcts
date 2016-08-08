#include "munit.h"
#include "../src/takeaway_state.h"
#include <stdio.h>

/*
 * Collection of unit tests for takeaway_state.c
 * Using the Munit unit testing framework
 */

// TESTS

// CREATE AND DESTRUCT
static void*
createSetup(const MunitParameter params[], void* data) {
    // Dynamically allocated
    return createTakeState(20, 1);
}

static void
createTearDown(void* fixture) {
    // use `make check` to ensure this properly frees
    destructTakeState((TakeState_s*) fixture);
}

static MunitResult
createTest(const MunitParameter params[], void* fixture) {
    TakeState_s* state = (TakeState_s*) fixture;

    munit_assert_uint8(state->pennies, ==, 20);

    // Should be flipped from the input (firstplayer)
    munit_assert_uint8(state->lplayer, ==, 2);

    return MUNIT_OK;
}

// DEEP COPY
static MunitResult
deepTest(const MunitParameter params[], void* data) {
    // Create the initial TakeState_s
    TakeState_s* init = createTakeState(20, 1);

    // Create the copy
    TakeState_s* copy = deepCopy(init);

    // Check to make sure the values are consistent
    munit_assert_uint8(init->pennies, ==, copy->pennies);
    munit_assert_uint8(init->lplayer, ==, copy->lplayer);

    // Ensure addresses are all different
    munit_assert_ptr(init, !=, copy);
    munit_assert_ptr(&(init->pennies), !=, &(copy->pennies));
    munit_assert_ptr(&(init->pennies), !=, &(copy->pennies));

    destructTakeState(init);
    destructTakeState(copy);

    return MUNIT_OK;
}

// PERFORM MOVE
static void*
performSetup(const MunitParameter params[], void* data) {
    return (void*) createTakeState(20, 2);
}

static void 
performTearDown(void* fixture) {
    free((TakeState_s*) fixture);
}

static MunitResult
performTest(const MunitParameter params[], void* fixture) {
    TakeState_s* state = (TakeState_s*) fixture;

    // allocate and assign moves
    uint8_t* m1 = (uint8_t*) malloc(sizeof(uint8_t));
    uint8_t* m2 = (uint8_t*) malloc(sizeof(uint8_t));
    uint8_t* m3 = (uint8_t*) malloc(sizeof(uint8_t));
    *m1 = 1;
    *m2 = 2;
    *m3 = 3;

    // Check performMove is functioning properly
    performMove(state, m1);
    munit_assert_uint8(state->pennies, ==, 19);
    munit_assert_uint8(state->lplayer, ==, 2);

    performMove(state, m2);
    munit_assert_uint8(state->pennies, ==, 17);
    munit_assert_uint8(state->lplayer, ==, 1);

    performMove(state, m3);
    munit_assert_uint8(state->pennies, ==, 14);
    munit_assert_uint8(state->lplayer, ==, 2);

    free(m1);
    free(m2);
    free(m3);

    return MUNIT_OK;
}

// GET MOVES LIST
static MunitResult
listTest(const MunitParameter params[], void* data) {
    TakeState_s* s1 = createTakeState(20, 1);
    TakeState_s* s2 = createTakeState(3, 2);
    TakeState_s* s3 = createTakeState(2, 1);
    TakeState_s* s4 = createTakeState(1, 2);

    // S1 testing with 20 pennies
    NodeQueue_s* q1 = getMovesList(s1);
    uint8_t d11 = *((uint8_t*) dequeue(q1));
    munit_assert_uint8(d11, ==, 1);
    uint8_t d12 = *((uint8_t*) dequeue(q1));
    munit_assert_uint8(d12, ==, 2);
    uint8_t d13 = *((uint8_t*) dequeue(q1));
    munit_assert_uint8(d13, ==, 3);
    munit_assert_null(dequeue(q1));
    
    // S2 testing with 3 pennies
    NodeQueue_s* q2 = getMovesList(s2);
    uint8_t d21 = *((uint8_t*) dequeue(q2));
    munit_assert_uint8(d21, ==, 1);
    uint8_t d22 = *((uint8_t*) dequeue(q2));
    munit_assert_uint8(d22, ==, 2);
    uint8_t d23 = *((uint8_t*) dequeue(q2));
    munit_assert_uint8(d23, ==, 3);
    munit_assert_null(dequeue(q2));

    // S3 testing with 2 pennies
    NodeQueue_s* q3 = getMovesList(s3);
    uint8_t d31 = *((uint8_t*) dequeue(q3));
    munit_assert_uint8(d31, ==, 1);
    uint8_t d32 = *((uint8_t*) dequeue(q3));
    munit_assert_uint8(d32, ==, 2);
    munit_assert_null(dequeue(q3));

    // S4 testing with 1 penny
    NodeQueue_s* q4 = getMovesList(s4);
    uint8_t d41 = *((uint8_t*) dequeue(q4));
    munit_assert_uint8(d41, ==, 1);
    munit_assert_null(dequeue(q4));

    // Destruct the test states
    destructTakeState(s1);
    destructTakeState(s2);
    destructTakeState(s3);
    destructTakeState(s4);

    return MUNIT_OK;
}

// TEST SUITE
static MunitTest test_suite_tests[] = {
    { (char*) "/takeaway/create/", createTest, createSetup,
        createTearDown, 0, NULL },
    { (char*) "/takeaway/deep/", deepTest, NULL, NULL, 0, NULL },
    { (char*) "/takeaway/perform/", performTest, performSetup,
        performTearDown, 0, NULL },
    { (char*) "/takeaway/list/", listTest, NULL, NULL, 0, NULL },
    { NULL, NULL, NULL, NULL, 0, NULL }
};

static const MunitSuite test_suite = {
    (char*) "takeawaysuite",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, (void*) "muhunit", argc, argv);
}
