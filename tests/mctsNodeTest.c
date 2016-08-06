#include "munit.h"
#include "../src/mcts_node.h"
#include <stdint.h>
#include <stdio.h>


// Macro to manually set up a moves list
#define create_moves(PTR, X, Y, Z)      \
    do {                                \
    PTR = construct_queue();            \
    int* TMPPTR1 = malloc(sizeof(int)); \
    int* TMPPTR2 = malloc(sizeof(int)); \
    int* TMPPTR3 = malloc(sizeof(int)); \
    *TMPPTR1 = X;                       \
    *TMPPTR2 = Y;                       \
    *TMPPTR3 = Z;                       \
    enqueue(PTR, (void*) TMPPTR1);      \
    enqueue(PTR, (void*) TMPPTR2);      \
    enqueue(PTR, (void*) TMPPTR3);      \
    } while (0)

// Creates a zero-set struct
#define zero_MCTS(ptr)                                      \
    do {                                                    \
        ptr = (mcts_node_s*) malloc(sizeof(mcts_node_s));   \
        memset(ptr, 0, sizeof(mcts_node_s));                \
    } while (0)

/*
#define blank_node(PTR) \
    PTR = (mcts_node_s*) malloc(sizeof(mcts_node_s)); \
    PTR->wins = 0;  \
    PTR->plays = 0; \
    PTR->
*/

// satifies childMovesGen_f in that it creates a move list
// off of a given state 
static node_queue_s*
genMoves(void* genstate) {
   int* state = (int*) genstate;
   int seed = *state;

   node_queue_s* moves_list;
   create_moves(moves_list, seed + 1, seed + 2, seed + 3);

   return moves_list;
}
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
                                        construct_queue(),
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

// CREATE ROOT
static void*
rootSetup(const MunitParameter params[], void* data) {
    mcts_node_s* fixture;
    uint8_t new_lplayer = 2;

    node_queue_s* moves_list;
    create_moves(moves_list, 1, 2, 3);


    // Create the root
    fixture = create_mcts_root(new_lplayer, moves_list);

    return fixture;
}

static void
rootTearDown(void* fixture){
    mcts_node_s* root = (mcts_node_s*) fixture;

    free_queue_data(root->rmoves);

    // Clean up the lists
    destruct_node_queue(root->rmoves);
    destruct_node_queue(root->children);

    free(root);
}
static MunitResult
rootTest(const MunitParameter params[], void* fixture) {
    mcts_node_s* root = (mcts_node_s*) fixture;

    munit_assert_uint32(root->wins, ==, 0);
    munit_assert_uint32(root->plays, ==, 0);
    munit_assert_uint8(root->lplayer, ==, 2);

    munit_assert_null(root->parent);
    munit_assert_not_null(root->rmoves);

    // Test the remaining moves list
    munit_assert_uint32(root->rmoves->elements, ==, 3);

    int firstMove = *((int*) root->rmoves->head->data);
    int secondMove = *((int*) root->rmoves->head->next->data);
    int thirdMove = *((int*) root->rmoves->tail->data);

    munit_assert_int(firstMove, ==, 1);
    munit_assert_int(secondMove, ==, 2);
    munit_assert_int(thirdMove, ==, 3);

    return MUNIT_OK;
}

// ADD CHILD
static void*
childSetup(const MunitParameter params[], void* data) {

    // Manually set up the root/parent
    node_queue_s* moves_list;
    create_moves(moves_list, 1, 2, 3);
    mcts_node_s* fixture = create_mcts_root(2, moves_list);

    return fixture;
}

static void
childTearDown(void* fixture) {
    mcts_node_s* parent = (mcts_node_s*) fixture;

    destruct_mcts_tree(parent);
}

static MunitResult
childTest(const MunitParameter params[], void* fixture) {
    mcts_node_s* parent = (mcts_node_s*) fixture;

    // Manually create moves list for child and populate
    node_queue_s* moves_list;
    create_moves(moves_list, 1, 2, 3);

    mcts_node_s* child = add_child(parent, genMoves);

    munit_assert_ptr(parent, ==, child->parent);

    // Check if lplayer properly toggles
    munit_assert_uint8(1, ==, child->lplayer);

    // Parent's children queue has been updated
    mcts_node_s* cListCheck = peek(parent->children);
    munit_assert_ptr(child, ==, cListCheck);
    
    // The child's move should be 1, 2, or 3
    int childMove = *((int*)child->move);
    if (childMove != 1 && childMove != 2 && childMove != 3) {
        return MUNIT_FAIL;
    }

    // Check to make sure the children's move list was generated correctly
    int a = *((int*) dequeue(child->rmoves));
    int b = *((int*) dequeue(child->rmoves));
    int c = *((int*) dequeue(child->rmoves));
    munit_assert_int(childMove + 1, ==, a);
    munit_assert_int(childMove + 2, ==, b);
    munit_assert_int(childMove + 3, ==, c);

    return MUNIT_OK;
}

// BACKPROPAGATION
static void*
backSetup(const MunitParameter params[], void* data) {
    mcts_node_s* root;
    mcts_node_s* first;
    mcts_node_s* second;
    
    // initialize the nodes to zeroed out MCTS nodes
    zero_MCTS(root);
    zero_MCTS(first);
    zero_MCTS(second);

    // set up their chain manually
    root->children = construct_queue();
    enqueue(root->children, (void*) first);

    first->children = construct_queue();
    enqueue(first->children, (void*) second);

    first->parent = root;
    second->parent = first;

    // we don't need to worry about the other memebers for this test so 
    // the fixture is now ready to be used for testing
    return second;        
}

static void
backTearDown(void* fixture) {
    // To try and keep this localized, manually destruct the chain 
    mcts_node_s* second = (mcts_node_s*) fixture;
    mcts_node_s* first = second->parent;
    mcts_node_s* root = first->parent;

    destruct_node_queue(first->children);
    destruct_node_queue(root->children);

    free(second);
    free(first);
    free(root);
}

static MunitResult
backTest(const MunitParameter params[], void* fixture) {
    mcts_node_s* leaf = (mcts_node_s*) fixture;
    mcts_node_s* mid = leaf->parent;
    mcts_node_s* root = mid->parent;
    
    backpropagation(3, leaf);

    // Check for proper backpropagation
    munit_assert_int32(3, ==, leaf->wins);
    munit_assert_int32(3, ==, mid->wins);
    munit_assert_int32(3, ==, root->wins);

    munit_assert_int32(1, ==, leaf->plays);
    munit_assert_int32(1, ==, mid->plays);
    munit_assert_int32(1, ==, root->plays);

    return MUNIT_OK;
}

// TEST SUITES
static MunitTest test_suite_tests[] = {
    { (char*) "/mctsnode/createNode/", createNodeTest, NULL,
        NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/mctsnodes/createroot/", rootTest, rootSetup, rootTearDown, 0, NULL },
    { (char*) "/mcttsnode/addchild/", childTest, childSetup,
        childTearDown, 0, NULL },
    { (char*) "/mctsnode/backprop/", backTest, backSetup,
        backTearDown, 0, NULL },
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
