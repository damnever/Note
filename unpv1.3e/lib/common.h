#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>

void err_msg(const char *fmt, ...);
void err_exit(const char *fmt, ...);

ssize_t readn(int fd, void *vptr, size_t n);
void writen(int fd, void *vptr, size_t n);


#endif
