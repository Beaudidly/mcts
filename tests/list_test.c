#include "munit.h"
#include "../src/node_queue.h"
#include <stdint.h>

/*
 * Collection of Unit tests for node_queue.c
 * Using the Munit unit testing framework
 */

// CONSTRUCT
static void*
construct_setup(const MunitParameter params[], void* data) {
    return construct();
}

void
construct_tear_down(void* fixture) {
    free(fixture);
}
static MunitResult
construct_test(const MunitParameter params[], void* fixture) {
    (void) params;

    node_queue_s* testQueue = (node_queue_s*) fixture; 

    munit_assert_null(testQueue->head);
    munit_assert_null(testQueue->tail);

    return MUNIT_OK;
}

// ENQUEUE
static void*
enqueue_setup(const MunitParameter params[], void* user_data) {
    node_queue_s* queue = construct();
    
    node_s* a = (node_s*) malloc(sizeof(node_s));
    node_s* b = (node_s*) malloc(sizeof(node_s));
    node_s* c = (node_s*) malloc(sizeof(node_s));

    enqueue(queue, a);
    enqueue(queue, b);
    enqueue(queue, c);

    return queue;
}

static MunitResult
enqueue_test(const MunitParameter params[], void* fixture) {
    node_queue_s* queue = (node_queue_s*) fixture;

    munit_assert_not_null(queue);
    munit_assert_not_null(queue->head);

    munit_assert_null(queue->tail->next);

    return MUNIT_OK;
}

void
enqueue_tear_down(void* fixture) {
    destruct(fixture);
}

// DEQUEUE
static MunitResult
dequeue_test(const MunitParameter params[], void* data) {
    node_queue_s* queue = construct();

    node_s* a = (node_s*) malloc(sizeof(node_s));
    node_s* b = (node_s*) malloc(sizeof(node_s));
    node_s* c = (node_s*) malloc(sizeof(node_s));

    enqueue(queue, a);
    enqueue(queue, b);
    enqueue(queue, c);

    munit_assert_uint32(queue->elements, ==, 3);

    dequeue(queue);
    dequeue(queue);
    dequeue(queue);

    munit_assert_uint32(queue->elements, ==, 0);

    munit_assert_null(queue->head);
    munit_assert_null(queue->tail);
    munit_assert_null(dequeue(queue));

    destruct(queue);

    return MUNIT_OK;
}

// PEEK
static MunitResult
peek_test(const MunitParameter params[], void* data) {
    node_queue_s* queue = construct();

    node_s* a = (node_s*) malloc(sizeof(node_s));
    node_s* b = (node_s*) malloc(sizeof(node_s));
    node_s* c = (node_s*) malloc(sizeof(node_s));

    enqueue(queue, a);
    enqueue(queue, b);
    enqueue(queue, c);

    peek(queue);

    munit_assert_uint32(queue->elements, ==, 3);

    destruct(queue);

    return MUNIT_OK;
}

// ISEMPTY
static MunitResult
isempty_test(const MunitParameter params[], void* data) {
    node_queue_s* queue = construct();

    uint8_t x = isempty(queue);

    munit_assert_uint8(x, ==, 1);

    node_s* a = (node_s*) malloc(sizeof(node_s));
    node_s* b = (node_s*) malloc(sizeof(node_s));
    node_s* c = (node_s*) malloc(sizeof(node_s));

    enqueue(queue, a);

    x = isempty(queue);
    munit_assert_uint8(x, ==, 0);

    enqueue(queue, b);
    enqueue(queue, c);

    x = isempty(queue);
    munit_assert_uint8(x, ==, 0);

    dequeue(queue);
    x = isempty(queue);
    munit_assert_uint8(x, ==, 0);

    dequeue(queue);
    x = isempty(queue);
    munit_assert_uint8(x, ==, 0);

    dequeue(queue);
    x = isempty(queue);
    munit_assert_uint8(x, ==, 1);



    destruct(queue);

    return MUNIT_OK;
}

// RANDOM REMOVE
static void*
rand_setup(const MunitParameter params[], void* data) {
    node_queue_s* queue = construct();

    enqueue(queue,(void*) "a");
    enqueue(queue,(void*) "b");
    enqueue(queue,(void*) "c");

    return queue;
}

static void
rand_tear_down(void *fixture) {
    destruct(fixture);
}

static MunitResult
rand_test(const MunitParameter params[], void* fixture) {
    node_queue_s* queue = (node_queue_s*) fixture;

    munit_assert_uint32(3, ==, queue->elements);

    rand_remove(queue);
    munit_assert_uint32(2, ==, queue->elements);

    rand_remove(queue);
    munit_assert_uint32(1, ==, queue->elements);
    munit_assert_ptr(queue->head, ==, queue->tail);

    rand_remove(queue);
    munit_assert_uint32(0, ==, queue->elements);
    munit_assert_null(queue->head);
    munit_assert_null(queue->tail);

    munit_assert_null(rand_remove(queue));

    return MUNIT_OK;
}

// TEST SUITE
static MunitTest test_suite_tests[] = {
    { (char*) "/list/construct", construct_test, construct_setup,
        construct_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/list/enqueue", enqueue_test, enqueue_setup,
        enqueue_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/list/dequeue", dequeue_test, NULL, NULL,
        MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/list/peek", peek_test, NULL, NULL,
        MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/list/isempty", isempty_test, NULL, NULL,
        MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/list/rand_remove", rand_test, rand_setup,rand_tear_down,
        MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char*) "testsuite",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc|1)]) {
    return munit_suite_main(&test_suite, (void*) "muhunit", argc, argv);
}
