#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "lib/common.h"

/*
 * The situation is different from the book, input EOF will recv nothing from server,
 * because client and server both in `sk_wait_data` state :-)
 */

#define MAXLINE 4096

void
str_echo(int sockfd)
{
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if ((fpin = fdopen(sockfd, "r")) == NULL) {
        err_exit("fdopen error");
    }
    if ((fpout = fdopen(sockfd, "w")) == NULL) {
        err_exit("fdopen error");
    }

    /* 1) line buffer */
    setvbuf(fpout,  line, _IOLBF, MAXLINE);

    for (;;) {
        if (fgets(line, MAXLINE, fpin) == NULL) {
            if (ferror(fpin)) {
                err_exit("fgets error");
            }
            break;
        }
        printf("recv: %s\n", line);
        if (fputs(line, fpout) == EOF) {
            err_exit("fputs error");
        }
        /* 2) flush it anyway.. */
        /* fflush(fpout); */
    }
}

void
str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    for (;;) {
        if (fgets(sendline, MAXLINE, fp) == NULL) {
            if (ferror(fp)) {
                err_exit("fgets error");
            }
            break;
        }
        writen(sockfd, sendline, strlen(sendline));
        if (readline(sockfd, recvline, MAXLINE) == 0) {
            err_exit("readline error");
        }
        if (fputs(recvline, stdout) == EOF) {
            err_exit("fputs error");
        }
    }
}

void
sig_child(int signal)
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("child %d terminated\n", pid);
    }
}

void
run_server(int port)
{
    int listenfd, connfd, reuseaddr = 1;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_exit("socket error");
    }
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) < 0) {
        err_exit("setsockopt error");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        err_exit("bind error");
    }
    if (listen(listenfd, 5) < 0) {
        err_exit("listen error");
    }


    if (signal(SIGCHLD, sig_child) == SIG_ERR) {
        err_exit("signal error");
    }

    for (;;) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
            err_exit("accept error");
        }
        if ((childpid = fork()) == 0) {
            if (close(listenfd) < 0) {
                err_exit("close error");
            }
            str_echo(connfd);
            exit(0);
        } else if (childpid < 0) {
            err_exit("fork error");
        }
        if (close(connfd) < 0) {
            err_exit("close error");
        }
    }
}

void
run_client(int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        err_exit("socket error");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        err_exit("inet_pton error");
    }
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        err_exit("connect error");
    }

    str_cli(stdin, sockfd);
    exit(0);
}

int main(int argc, char *argv[])
{
    int port;
    if (argc != 3) {
        err_exit("wrong useage: %s <server/client> <port>", argv[0]);
    }

    port = atoi(argv[2]);
    if (strcmp(argv[1], "server") == 0) {
        run_server(port);
    } else if (strcmp(argv[1], "client") == 0) {
        run_client(port);
    } else {
        err_exit("unknown argument '%s'", argv[1]);
    }

    return 0;
}
