/*
 * size_t: unsigned type.
 * ssize_t: signed type, simailar to size_t, use it when you want to return a error value.
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"


ssize_t _readn(int fd, void *vptr, size_t n);
ssize_t _writen(int fd, void *vptr, size_t n);


ssize_t
readn(int fd, void *vptr, size_t n)
{
    ssize_t nread;

    if ( (nread = _readn(fd, vptr, n)) < 0) {
        err_exit("readn error");
    }
    return nread;
}


void
writen(int fd, void *vptr, size_t n)
{
    if (_writen(fd, vptr, n) - n != 0) {
        err_exit("writen error");
    }
}


ssize_t
_readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = (char *)vptr;
    nleft = n;
    nread = 0;
    for (; nleft > 0;) {
        if ((nread = read(fd, ptr, n)) < 0) {
            if (errno == EINTR) {  // read again
                nread = 0;
            } else {
                return -1;
            }
        } else if (nread == 0) {  // EOF
            break;
        }
        nleft -= nread;
        ptr += nread;
    }

    return (n - nleft);
}

ssize_t
_writen(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwrite;
    char *ptr;

    ptr = (char *)vptr;
    nleft = n;
    nwrite = 0;
    for (; nleft > 0;) {
        if ((nwrite = write(fd, ptr, nleft)) <= 0) {
            if (nwrite < 0 && errno == EINTR) {  // write again
                nwrite = 0;
            } else {
                return -1;
            }
        }
        nleft -= nwrite;
        ptr += nwrite;
    }

    return n;
}
