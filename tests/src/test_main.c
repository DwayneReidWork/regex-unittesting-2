#include "test_example.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

const struct CMUnitTest unit_tests[] = {

    // { } REQUIRED Edit the test list here
    cmocka_unit_test(test_example)};

int main(void)
{
    return cmocka_run_group_tests(unit_tests, NULL, NULL);
}
