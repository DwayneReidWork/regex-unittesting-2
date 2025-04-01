/*
This program can be run from the command line passing in a string and will search for the string and on a successful match will return the matched working directly as well as file stats.
*/

#define _XOPEN_SOURCE 500
#include "regex_and_testing.h"

#include <ftw.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

regex_t regex;

// declare and assign it
ftw_callback_t callback_ptr = ftw_callback;

int ftw_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    /*const char *fpath: The path of the current file or directory.
    const struct stat *sb: A pointer to a stat structure containing information about the file.
    int typeflag: Indicates whether the current file is a directory (FTW_D), regular file (FTW_F), or another type.
    struct FTW *ftwbuf: Contains information about the current file, including the depth of the directory tree.*/
    if (!fpath || fpath < 0)
    {
        printf("Error with file path pointer.");
        return -1;
    }
    else if (!sb || sb < 0)
    {
        printf("Error with struct pointer.");
        return -1;
    }
    else if (!ftwbuf || ftwbuf < 0)
    {
        printf("Error with file information pointer.");
        return -1;
    }

    if (typeflag == FTW_F)
    { // Only process files
        if (regexec(&regex, fpath, 0, NULL, 0) == 0)
        {
            printf("Match found: %s\n", fpath);
            // shows filetype, directory depth, size of file, path name, base path offset, and relative path (i think)
            display_info(fpath, sb, typeflag, ftwbuf);
        }
    }
    return 0;
}

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
    if (!fpath || fpath < 0)
    {
        printf("Error with file path pointer.");
        return -1;
    }
    else if (!sb || sb < 0)
    {
        printf("Error with struct pointer.");
        return -1;
    }
    else if (!ftwbuf || ftwbuf < 0)
    {
        printf("Error with file information pointer.");
        return -1;
    }
    /* %-3 This specifies that the output will be a string (s), left-aligned (-), with a width of 3 characters. The string will be padded with spaces if it is shorter than 3 characters.*/

    /*%2d This is for an integer (d) to be printed with a width of 2 characters. If the integer is less than 2 digits, it will be padded with spaces. */

    // Big print statement is overkill becuase callback is only interested in the FTW_F flag. (but good to know for future potential implementation.)

    printf("%-3s %2d ",
           (tflag == FTW_D) ? "d" : (tflag == FTW_DNR) ? "dnr"
                                : (tflag == FTW_DP)    ? "dp"
                                : (tflag == FTW_F)     ? "f"
                                : (tflag == FTW_NS)    ? "ns"
                                : (tflag == FTW_SL)    ? "sl"
                                : (tflag == FTW_SLN)   ? "sln"
                                                       : "???",
           /*If tflag == FTW_D: Print "d" for directory.
           tflag == FTW_DNR: Print "dnr" for directory that could not be read.
           tflag == FTW_DP: Print "dp" for directory, post traversal.
           tflag == FTW_F: Print "f" for a regular file.
           tflag == FTW_NS: Print "ns" for a file or directory that could not be stat-ed (not found).
           tflag == FTW_SL: Print "sl" for a symbolic link.
           tflag == FTW_SLN: Print "sln" for a symbolic link that points to a nonexistent file.
           tflag doesn't match any of these values, print "???".*/
           ftwbuf->level);

    if (tflag == FTW_NS)
        // If file cant be statted print dashes in file size
        printf("-------");

    else
        // print the file size using %7jd (right-aligned within 7 spaces
        printf("%7jd", (intmax_t)sb->st_size);

    printf("   %-40s %d %s\n",
           fpath, ftwbuf->base, fpath + ftwbuf->base);

    return 0; // To tell nftw() to continue
}

int check_args(int argc, char *argv[])
{
    if (2 != argc)
    {
        printf("Usage: %s <regex>\n", argv[0]);
        return -1;
    }
    return 0;
}

int compile_regex(int argc, char *argv[])
{
    int status = regcomp(&regex, argv[1], REG_EXTENDED);

    if (0 != status)
    {
        char errbuf[256];
        regerror(status, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp error: %s\n", errbuf);
        return -1;
    }
    return 0;
}

int search_through_tree(char dirpath[], ftw_callback_t callback_ptr)
{
    if (!callback_ptr)
    {
        fprintf(stderr, "Error: NULL callback function provided.\n");
        return -1;
    }

    struct stat dir_stat;
    // checks that the dir path exists and is actually a directory.
    if (0 != stat(dirpath, &dir_stat) || !S_ISDIR(dir_stat.st_mode))
    {
        fprintf(stderr, "Error: Invalid directory path '%s'\n", dirpath);
        return -1;
    }

    // Use the provided callback function
    if (-1 == nftw(dirpath, callback_ptr, 20, FTW_PHYS))
    {
        fprintf(stderr, "NFTW Error:'%d'\n", nftw(dirpath, callback_ptr, 20, FTW_PHYS));
        return -1;
    }
    return 0;
}