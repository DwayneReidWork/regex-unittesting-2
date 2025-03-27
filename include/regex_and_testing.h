#ifndef REGEX_AND_TESTING_H
#define REGEX_AND_TESTING_H

#define _XOPEN_SOURCE 500

#include <ftw.h>
#include <regex.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Global regex variable
// use extern to keep it from being redeclared in multiple c files.
extern regex_t regex;

int check_args(int argc, char *argv[]);

int ftw_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

#endif // REGEX_AND_TESTING_H