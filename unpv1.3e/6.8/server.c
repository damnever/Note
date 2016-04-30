#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../lib/common.h"

#undef BACKLOG
#define BACKLOG 5
#define MAX_READ_LINE 20


int max_fds();
void close_fd(int fd);

int main(int argc, char *argv[])
{
    int idx, nready, nread, nfds, open_max = max_fds();
    int srv_fd, cli_fd;
    char buf[MAX_READ_LINE];
    socklen_t addr_len;
    struct sockaddr_in srv_addr, cli_addr;
    struct pollfd poll_fds[open_max];

    if (argc != 2) {
        err_exit("Server port required");
    }

    if ((srv_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        err_exit("socket error");
    }

    bzero(&srv_addr, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(srv_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
        err_exit("bind error");
    }
    if (listen(srv_fd, BACKLOG) < 0) {
        err_exit("listen error");
    }

    poll_fds[0].fd = srv_fd;
    poll_fds[0].events = POLLIN;
    for (idx = 1; idx <= open_max; ++idx) {
        poll_fds[idx].fd = -1;
    }
    nfds = 0;

    printf("Server: tcp://localhost:%s ...\n", argv[1]);

    for (;;) {
        if((nready = poll(poll_fds, nfds + 1, -1)) < 0) {
            err_exit("poll error");
        }

        if (poll_fds[0].revents & POLLIN) { // new connection come in
            addr_len = sizeof(cli_addr);
accept_again:
            if ((cli_fd = accept(srv_fd, (struct sockaddr *)&cli_addr, &addr_len)) < 0) {
#ifdef EPROTO
                if (errno == EPROTO)  // SVR4: protocol error
#else
                if (errno == ECONNABORTED)  // POSIX: software caused connection abort
#endif
                    goto accept_again;
                err_exit("accept error");
            }

            for (idx = 1; idx < open_max; ++idx) {
                if (poll_fds[idx].fd < 0) {
                    poll_fds[idx].fd = cli_fd;
                    poll_fds[idx].events = POLLIN;
                    nfds = idx;
                    break;
                }
            }

            if (idx == open_max) {
                err_msg("too many connections");
            }

            if ((--nready) <= 0) {  // no more readable conn
                continue;
            }
        }

        for (idx = 1; idx <= open_max; ++idx) {
            if (poll_fds[idx].fd < 0) {
                continue;
            }

            if (poll_fds[idx].revents & (POLLIN | POLLERR)) {
                if ((nread = readn(poll_fds[idx].fd, buf, MAX_READ_LINE)) < 0) {
                    if (errno == ECONNRESET) {  // connection reset by peer: cli SO_LINGER
                        close_fd(poll_fds[idx].fd);
                        poll_fds[idx].fd = -1;
                    } else {
                        err_exit("read error");
                    }
                } else if (nread == 0) {  // conn closed
                    close_fd(poll_fds[idx].fd);
                    poll_fds[idx].fd = -1;
                } else {
                    writen(poll_fds[idx].fd, buf, nread);
                }
            }

            if ((--nready) <= 0) {
                break;
            }
        }

    }

    return 0;
}

void
close_fd(int fd)
{
    if (close(fd) < 0) {
        err_msg("close client error");
    }
}

int max_fds()
{
    return sysconf(_SC_OPEN_MAX);
}
