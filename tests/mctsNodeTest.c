#include "munit.h"
#include "../src/mcts_node.h"
#include <stdint.h>

/*
 * Collection of unit tests for mcts_node.c
 * Using the Munit unit testing framkework
 */

/* FUNCTION UNIT TESTS */

// CREATE MCTS NODE
static MunitResult
createNodeTest(const MunitParameter params[], void* data) {
    // This just gets rid of compiler warnings
    (void) params;
    (void) data;

    int testMove = 5; 
    
    mcts_node_s* root = create_mcts_node( 1,
                                        construct(),
                                        (void*) &testMove,
                                        NULL);

    munit_assert_uint32(root->wins, ==, 0);
    munit_assert_uint32(root->plays, ==, 0);
    munit_assert_uint8(root->lplayer, ==, 1);

    munit_assert_null(root->parent);
    munit_assert_not_null(root->rmoves);
    munit_assert_null(root->rmoves->head);

    munit_assert_not_null(root->children);
    munit_assert_null(root->children->head);
    
    //TODO finish writing assertions

    return MUNIT_OK;
}


// TEST SUITES
static MunitTest test_suite_tests[] = {
    { (char*) "/mctsnode/createNode/", createNodeTest, NULL,
        NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char*) "mctsnodesuite",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, (void*) "muhunit", argc, argv);
}
