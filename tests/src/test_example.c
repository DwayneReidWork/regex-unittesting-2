#include "common.h"
#include "example.h"

#include <stdio.h>
#include <assert.h>
#include <cmocka.h>

/// @brief An example of a very simple test in cmocka
/// @param state
void test_example(void **state)
{
    int inputs[5] = {
        -3, 0, 1, 5, 12};
    int expected[5] = {
        9, 0, 1, 25, 144};

    int i = 0;
    int result = 0;

    for (i = 0; i < 5; i++)
    {
        result = example(inputs[i]);
        // can add printfs for debugging/info if need be
        // printf("Input: %d, Expected: %d, Result: %d\n", inputs[i], expected[i], result);
        assert_true(result == expected[i]);
    }
}