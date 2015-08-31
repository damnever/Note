#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Implement dup2 by dup.
 * Test use F_SETFL as fcntl cmd argument.
 */

int
my_dup2(int fd, int fd2)
{
    int fd_cnt, tmp_fd, idx, *fds;

    if(fd == fd2) {
        return fd2;
    }

    if(-1 == close(fd2)) {
        fprintf(stderr, "close(%d) error\n", fd2);
        return -1;
    }
    tmp_fd = 0;
    fd_cnt = 0;
    if(NULL == (fds = (int*)malloc(fd2 * sizeof(int)))) {
        fprintf(stderr, "malloc error\n");
        return -1;
    }

    while(tmp_fd < fd2) {
        tmp_fd = dup(fd);
        if(-1 == tmp_fd) {
            fprintf(stderr, "dup(%d) error\n", fd);
            return -1;
        }
        if(fd2 == tmp_fd) {
            break;
        }
        fds[fd_cnt++] = tmp_fd;
    }
    if(tmp_fd != fd2) {
        return -1;
    }

    for(idx = 0; idx < fd_cnt; idx++) {
        if(-1 == close(fds[idx])) {
            fprintf(stderr, "close(%d) error\n", fds[idx]);
            return -1;
        }
    }

    free(fds);

    return fd2;
}

/* Code borrow from apue.3e P67 Pic3-11. */
void
print_fdfl(int fd)
{
    int val;

    if((val = fcntl(fd, F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl error for fd %d\n", fd);
        return;
    }

    switch(val & O_ACCMODE) {
        case O_RDONLY:
            printf("READ ONLY");
            break;
        case O_WRONLY:
            printf("WRITE ONLY");
            break;
        case O_RDWR:
            printf("READ WRITE");
            break;
        default:
            fprintf(stderr, "unknown access mode");
    }

    if(val & O_APPEND) {
        printf(", APPEND");
    }
    if(val & O_NONBLOCK) {
        printf(", NONBLOCKING");
    }
    if(val & O_SYNC) {
        printf(", SYNCHRONOUS WRITES");
    }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if(val & O_FSYNC)
        printf(", SYNCHRONOUS WRITES");
#endif

    printf("\n");
}

int
main()
{
    int fd = open("./3.2_implement_dup2.c", O_RDONLY);
    int fd2 = open("./3.2_implement_dup2.c", O_RDWR);
    print_fdfl(fd);
    print_fdfl(fd2);

    fd2 = my_dup2(fd, fd2);
    print_fdfl(fd);
    print_fdfl(fd2);

    // If success, fd and fd2 will be change.
    fcntl(fd, F_SETFL, O_APPEND);
    print_fdfl(fd);
    print_fdfl(fd2);

    return 0;
}
