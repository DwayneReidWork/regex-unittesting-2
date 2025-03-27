#define _XOPEN_SOURCE 500
#include "regex_and_testing.c"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (check_args(argc, argv) != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
