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

/*const char *fpath: The path of the current file or directory.
const struct stat *sb: A pointer to a stat structure containing information about the file.
int typeflag: Indicates whether the current file is a directory (FTW_D), regular file (FTW_F), or another type.
struct FTW *ftwbuf: Contains information about the current file, including the depth of the directory tree.*/
int ftw_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
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
        // If file cant be statted ptint dashes in file size
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
    if (argc != 2)
    {
        printf("Usage: %s <regex>\n", argv[0]);
        return -1;
    }

    int status = regcomp(&regex, argv[1], REG_EXTENDED);
    char dirpath[] = ".";

    if (status != 0)
    {
        char errbuf[256];
        regerror(status, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp error: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }

    // dirpath = where traversing starts
    // callback called for each file encountered on the traversal
    // 20 = max distance to traverse down
    // FTW_phys = treat symbolic links as physical links and skip them
    if (nftw(dirpath, ftw_callback, 20, FTW_PHYS) == -1)
    {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    // free regex compilers
    regfree(&regex);
    return 0;
}