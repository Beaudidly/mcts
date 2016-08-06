#include "munit.h"
#include "../src/node_queue.h"
#include <stdint.h>

/*
 * Collection of unit tests for node_queue.c
 * Using the Munit unit testing framework
 */

// CONSTRUCT
static void*
constructSetup(const MunitParameter params[], void* data) {
    return constructQueue();
}

void
constructTearDown(void* fixture) {
    free(fixture);
}
static MunitResult
constructTest(const MunitParameter params[], void* fixture) {
    (void) params;

    NodeQueue_s* testQueue = (NodeQueue_s*) fixture; 

    munit_assert_null(testQueue->head);
    munit_assert_null(testQueue->tail);

    return MUNIT_OK;
}

// ENQUEUE
static void*
enqueueSetup(const MunitParameter params[], void* user_data) {
    NodeQueue_s* queue = constructQueue();
    
    enqueue(queue,(void*) "a" );
    enqueue(queue,(void*) "b");
    enqueue(queue,(void*) "c");

    return queue;
}

static MunitResult
enqueueTest(const MunitParameter params[], void* fixture) {
    NodeQueue_s* queue = (NodeQueue_s*) fixture;

    munit_assert_not_null(queue);
    munit_assert_not_null(queue->head);

    munit_assert_null(queue->tail->next);

    return MUNIT_OK;
}

void
enqueueTearDown(void* fixture) {
    destructNodeQueue(fixture);
}

// DEQUEUE
static MunitResult
dequeueTest(const MunitParameter params[], void* data) {
    NodeQueue_s* queue = constructQueue();

    enqueue(queue,(void*) "a" );
    enqueue(queue,(void*) "b");
    enqueue(queue,(void*) "c");

    munit_assert_uint32(queue->elements, ==, 3);

    dequeue(queue);
    dequeue(queue);
    dequeue(queue);

    munit_assert_uint32(queue->elements, ==, 0);

    munit_assert_null(queue->head);
    munit_assert_null(queue->tail);
    munit_assert_null(dequeue(queue));

    destructNodeQueue(queue);

    return MUNIT_OK;
}

// PEEK
static MunitResult
peek_test(const MunitParameter params[], void* data) {
    NodeQueue_s* queue = constructQueue();


    enqueue(queue,(void*) "a" );
    enqueue(queue,(void*) "b");
    enqueue(queue,(void*) "c");

    peek(queue);

    munit_assert_uint32(queue->elements, ==, 3);

    destructNodeQueue(queue);

    return MUNIT_OK;
}

// ISEMPTY
static MunitResult
isemptyTest(const MunitParameter params[], void* data) {
    NodeQueue_s* queue = constructQueue();

    uint8_t x = isempty(queue);

    munit_assert_uint8(x, ==, 1);


    enqueue(queue, (void*) "a");

    x = isempty(queue);
    munit_assert_uint8(x, ==, 0);

    enqueue(queue, (void*) "b");
    enqueue(queue, (void*) "c");

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



    destructNodeQueue(queue);

    return MUNIT_OK;
}

// RANDOM REMOVE
static void*
randSetup(const MunitParameter params[], void* data) {
    NodeQueue_s* queue = constructQueue();

    enqueue(queue,(void*) "a");
    enqueue(queue,(void*) "b");
    enqueue(queue,(void*) "c");

    return queue;
}

static void
randTearDown(void *fixture) {
    destructNodeQueue(fixture);
}

static MunitResult
randTest(const MunitParameter params[], void* fixture) {
    NodeQueue_s* queue = (NodeQueue_s*) fixture;

    munit_assert_uint32(3, ==, queue->elements);

    randRemove(queue);
    munit_assert_uint32(2, ==, queue->elements);

    randRemove(queue);
    munit_assert_uint32(1, ==, queue->elements);

    munit_assert_ptr(queue->head, ==, queue->tail);

    randRemove(queue);
    munit_assert_uint32(0, ==, queue->elements);
    munit_assert_null(queue->head);
    munit_assert_null(queue->tail);

    munit_assert_null(randRemove(queue));

    return MUNIT_OK;
}

// TEST SUITE
static MunitTest test_suite_tests[] = {
    { (char*) "/queue/construct", constructTest, constructSetup,
        constructTearDown, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/queue/enqueue", enqueueTest, enqueueSetup,
        enqueueTearDown, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/queue/dequeue", dequeueTest, NULL, NULL,
        MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/queue/peek", peek_test, NULL, NULL,
        MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/queue/isempty", isemptyTest, NULL, NULL,
        MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/queue/randRemove", randTest, randSetup,randTearDown,
        MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char*) "queuesuite",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, (void*) "muhunit", argc, argv);
}
