#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

/*
 * A simple program to copy a directory and file tree.
 */

#define BUFFER_SIZE 4096

static void walk_and_copy(char *dir, char *des);
static void copy(char *src, char *des);
static void err_msg(const char *msg);
static void join_path(char **fullpath, int num_path, ...);
static bool endswith(char *str, char c);

int
main(int argc, char *argv[])
{
    if (3 != argc) {
        err_msg("Expected source directory and destination directory.\n"
                "Usage: copy_tree <source directory> <destination directory>\n");
    }
    walk_and_copy(argv[1], argv[2]);

    return 0;
}

static void
walk_and_copy(char *dir, char *des)
{
    struct stat stbuf;
    DIR *dp;
    struct dirent *dirp;
    char *fullpath = NULL, *despath = NULL;

    if ((dp = opendir(dir)) == NULL) {
        err_msg("opendir error\n");
    }
    while ((dirp = readdir(dp)) != NULL) {
        // Ignore current directory and parent directory.
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }

        join_path(&fullpath, 2, dir, dirp->d_name);
        join_path(&despath, 2, des, dirp->d_name);

        if (lstat(fullpath, &stbuf) < 0) {
            err_msg("lstat error\n");
        }
        if (S_ISDIR(stbuf.st_mode)) {  // Is directory.
            printf("\e[1;31m==>\e[0m %s\n", fullpath);
            if (mkdir(despath, 0755) < 0) {
                if (EEXIST != errno) {  // Directory exists.
                    err_msg("mkdir error\n");
                }
            }
            // Recursive.
            walk_and_copy(fullpath, despath);
        } else {  // Not directory.
            printf("%s \e[1;32m--->>\e[0m %s\n", fullpath, despath);
            copy(fullpath, despath);
        }
        free(fullpath);
        free(despath);
        fullpath = NULL;
        despath = NULL;
    }
    if (closedir(dp) < 0) {
        err_msg("closedir error\n");
    }
}

/* Copy source file to destination */
static void
copy(char *src, char *des)
{
    FILE *fsrc, *fdes;
    size_t n;
    char buffer[BUFFER_SIZE];

    if ((fsrc = fopen(src, "rb")) == NULL) {
        err_msg("open source file error\n");
    }
    if ((fdes = fopen(des, "wb")) == NULL) {
        err_msg("open destination file error\n");
    }

    while ((n = fread(buffer, 1, BUFFER_SIZE, fsrc)) != 0) {
        if (fwrite(buffer, 1, n, fdes) != n) {
            err_msg("fwrite error\n");
        }
    }
    if (n != 0) {
        err_msg("fread error\n");
    }

    if (fclose(fsrc) == EOF || fclose(fdes) == EOF) {
        err_msg("fclose error\n");
    }
}

/* Show error message and exit */
static void
err_msg(const char *msg)
{
    fputs(msg, stderr);
    exit(1);
}

/* Join multiple paths to fullpath. */
static void
join_path(char **fullpath, int num_path, ...)
{
    int len, copyed, i;
    char *tmp;
    char *args[num_path];
    va_list ap;

    len = num_path - 1;
    va_start(ap, num_path);
    for (i = 0; i < num_path; ++i) {
        tmp = va_arg(ap, char *);
        len += strlen(tmp);
        if (i != num_path - 1 && endswith(tmp, '/')) {
            len -= 1;
        }
        args[i] = tmp;
    }
    va_end(ap);

    *fullpath = (char *)malloc(len + 1);
    memset(*fullpath, 0, len + 1);

    copyed = 0;
    for (i = 0; i < num_path; ++i) {
        strcpy(&(*fullpath)[copyed], args[i]);
        copyed += strlen(args[i]);
        if (i != num_path - 1 && !endswith(args[i], '/')) {
            strcpy(&(*fullpath)[copyed], "/");
            copyed += 1;
        }
    }
}

/* Check string wether is endswith character */
static bool
endswith(char *str, char c)
{
    if (str[strlen(str) - 1] == c) {
        return true;
    }
    return false;
}
