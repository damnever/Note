#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/common.h"

#define MAX_INPUT_LINE 20
#define max(x, y) ({ \
    __typeof__(x) _x = (x); \
    __typeof__(y) _y = (y); \
    (void) (&_x == &_y); \
    _x > _y ? _x : _y; \
})


void str_cli(FILE *fd, int sockfd);


int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in addr;

    if (argc != 3) {
        err_exit("Server addr and port required");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        err_exit("socket error");
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family =AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) < 0) {
        err_exit("inet_pton error");
    }

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        err_exit("connect error");
    }

    str_cli(stdin, sockfd);

    return 0;
}

void
str_cli(FILE *fp, int sockfd)
{
    int max_fd, stdin_eof;
    fd_set rset;
    char buf[MAX_INPUT_LINE];
    int n;

    stdin_eof = 0;
    FD_ZERO(&rset);

    for (; ; ) {
        if (stdin_eof == 0) {
            FD_SET(fileno(fp), &rset);
        }
        FD_SET(sockfd, &rset);
        max_fd = max(fileno(fp), sockfd) + 1;
        if (select(max_fd, &rset, NULL, NULL, NULL) < 0) {
            err_exit("select error");
        }

        if (FD_ISSET(sockfd, &rset)) {
            if ((n = read(sockfd, buf, MAX_INPUT_LINE)) < 0) {
                err_exit("read from sock error");
            } else if (n == 0) {
                if (stdin_eof == 1) {
                    return;
                }
            }
            if (write(fileno(stdout), buf, n) != n) {
                err_exit("write to stdout error");
            }
        }

        if (FD_ISSET(fileno(fp), &rset)) {
            if ((n = read(fileno(fp), buf, MAX_INPUT_LINE)) < 0) {
                err_exit("read from stdin error");
            } else if (n == 0) {
                stdin_eof = 1;
                if (shutdown(sockfd, SHUT_WR) < 0) {
                    err_exit("shutdown error");
                }
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            if (write(sockfd, buf, n) != n) {
                err_exit("write to sock error");
            }
        }
    }
}
