#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "common.h"


#undef MAXLINE
#define MAXLINE 23


void _error_msg(const char *fmt, va_list ap);

void
err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    _error_msg(fmt, ap);
    va_end(ap);
}

void
err_exit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    _error_msg(fmt, ap);
    va_end(ap);

    exit(1);
}

void
_error_msg(const char *fmt, va_list ap)
{
    int err, n;
    char buf[MAXLINE + 1];

    err = errno;
    vsnprintf(buf, MAXLINE, fmt, ap);
    if (err != 0) {
        n = strlen(buf);
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(err));
    }
    strcat(buf, "\n");

    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}
