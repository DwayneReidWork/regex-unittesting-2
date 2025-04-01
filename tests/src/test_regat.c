#include "regex_and_testing.h"
#include "test_regat.h"

#include <ftw.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

int argc;
int result;

// Mock callback for testing
int mock_ftw_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    // prints entire directory VVV
    // printf("Mock callback invoked for: %s\n", fpath);

    // CAN JUST HAVE THE FUNCTION RETURN 0 TO FULFIL THE FACE THAT ITS BEING CALLED!!!!!
    return 0;
}

static void test_check_args(void **state)
{
    argc = 2;
    char *testArgV[] = {"program_name", "test_search_term"};

    result = check_args(argc, &testArgV[1]);
    assert_int_equal(result, 0);
}

static void test_check_args_invalid_number_of_args(void **state)
{
    // invalid number of args
    argc = 3;
    char *testArgV[] = {"program_name", "test_search_term", "search_that_breaks_it"};

    result = check_args(argc, &testArgV[1]);
    assert_int_equal(result, -1);
}

static void test_compile_regex(void **state)
{
    argc = 2;
    char *testArgV[] = {"program_name", "test_search_term"};
    result = compile_regex(argc, &testArgV[1]);
    assert_int_equal(result, 0);
}

static void test_compile_regex_invalid_regex(void **state)
{
    argc = 2;
    char *testArgV[] = {"program_name", "**fail**"};
    result = compile_regex(argc, testArgV);
    assert_int_equal(result, -1);
}

static void test_search_through_tree(void **state)
{
    char dirpath[] = ".";
    result = search_through_tree(dirpath, mock_ftw_callback);
    printf("search tree result: %d\n", result);
    assert_int_equal(result, 0);
}

static void test_search_through_tree_invalid_dirpath(void **state)
{
    char dirpath[] = ".fail";
    result = search_through_tree(dirpath, mock_ftw_callback);
    printf("search tree fail result: %d\n", result);
    assert_int_equal(result, -1);
}

static void test_search_through_tree_invalid_callback_func(void **state)
{
    char dirpath[] = ".";
    result = search_through_tree(dirpath, NULL);
    printf("search tree fail result: %d\n", result);
    assert_int_equal(result, -1);
}

int main(void)
{
    const struct CMUnitTest unit_tests[] = {

        // { } REQUIRED Edit the test list here
        cmocka_unit_test(test_check_args),
        cmocka_unit_test(test_check_args_invalid_number_of_args),
        cmocka_unit_test(test_compile_regex),
        cmocka_unit_test(test_compile_regex_invalid_regex),
        cmocka_unit_test(test_search_through_tree),
        cmocka_unit_test(test_search_through_tree_invalid_dirpath),
        cmocka_unit_test(test_search_through_tree_invalid_callback_func),
    };

    return cmocka_run_group_tests(unit_tests, NULL, NULL);
}
