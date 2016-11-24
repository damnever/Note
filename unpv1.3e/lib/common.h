#ifndef _COMMON_H
#define _COMMON_H
#include <unistd.h>

#define MAXLINE 4096

/* error.c */
void err_msg(const char *fmt, ...);
void err_exit(const char *fmt, ...);

/* read_write_n.c */
ssize_t readn(int fd, void *vptr, size_t n);
void writen(int fd, void *vptr, size_t n);

/* read_write_line.c */
ssize_t readlinebuf(void **vptrptr);
ssize_t readline(int fd, void *ptr, size_t maxlen);

#endif
