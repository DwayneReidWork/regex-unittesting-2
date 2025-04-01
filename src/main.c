#define _XOPEN_SOURCE 500
#include "regex_and_testing.c"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

    if (-1 == check_args(argc, argv))
        return EXIT_FAILURE;

    if (0 != compile_regex(argc, argv))
        return EXIT_FAILURE;

    return search_through_tree(".", callback_ptr);
    regfree(&regex);
}
