#include "munit.h"
#include "../src/node_queue.h"

static MunitResult
construct_test(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    node_queue_s* testQueue = construct();

    munit_assert_null(testQueue);

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { (char*) "/list/construct", construct_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
