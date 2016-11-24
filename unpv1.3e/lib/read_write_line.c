#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "common.h"


static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];


static ssize_t
_read(int fd, char *ptr)
{
    if (read_cnt <= 0) {
again:
        if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR) {
                goto again;
            }
            return -1;
        } else if (read_cnt == 0) {
            return 0;
        } else {
            read_ptr = read_buf;
        }
    }

    read_cnt -= 1;
    *ptr = *read_ptr++;
    return 1;
}

ssize_t
_readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; ++n) {
        if ((rc = _read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n') break;
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1);
        } else {
            return -1;
        }
    }

    *ptr = 0;
    return n;
}

ssize_t
readlinebuf(void **vptrptr)
{
    if (read_cnt)
        *vptrptr = read_ptr;
    return read_cnt;
}

ssize_t
readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t n;

    if ((n = _readline(fd, ptr, maxlen)) < 0) {
        err_exit("_readline error");
    }
    return n;
}
