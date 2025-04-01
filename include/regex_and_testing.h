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

// define the function prt
typedef int (*ftw_callback_t)(const char *, const struct stat *, int, struct FTW *);

int check_args(int argc, char *argv[]);

int compile_regex(int argc, char *argv[]);

int search_through_tree(char dirpath[], ftw_callback_t callback_ptr);

int ftw_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

#endif // REGEX_AND_TESTING_H