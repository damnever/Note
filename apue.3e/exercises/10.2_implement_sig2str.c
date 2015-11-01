#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

int my_sig2str(int signo, char *str);

int
main(int argc, char *argv[])
{
    char str[20];

    if (argc != 2) {
        fprintf(stderr, "Expect one argument, got %d.\n", (argc - 1));
        exit(1);
    }

    if (my_sig2str(atoi(argv[1]), str) < 0) {
        fprintf(stderr, "sig2str error\n");
        exit(1);
    }
    printf("%s\n", str);

    return 0;
}

int
my_sig2str(int signo, char *str)
{
    // XXX: case..........#ifdef...........
    switch (signo) {
        case SIGABRT:
            strcpy(str, "ABRT");
            break;
        case SIGALRM:
            strcpy(str, "ALRM");
            break;
        case SIGCHLD:
            strcpy(str, "CHLD");
            break;
        case SIGCONT:
            strcpy(str, "CONT");
            break;
        case SIGFPE:
            strcpy(str, "FPE");
            break;
        case SIGHUP:
            strcpy(str, "HUP");
            break;
        case SIGILL:
            strcpy(str, "ILL");
            break;
        case SIGINT:
            strcpy(str, "INT");
            break;
        case SIGKILL:
            strcpy(str, "KILL");
            break;
        case SIGPIPE:
            strcpy(str, "PIPE");
            break;
        case SIGQUIT:
            strcpy(str, "QUIT");
            break;
        case SIGSEGV:
            strcpy(str, "SEGV");
            break;
        case SIGSTOP:
            strcpy(str, "STOP");
            break;
        case SIGTERM:
            strcpy(str, "TERM");
            break;
        case SIGTSTP:
            strcpy(str, "TSTP");
            break;
        case SIGTTIN:
            strcpy(str, "TTIN");
            break;
        case SIGTTOU:
            strcpy(str, "TTOU");
            break;
        case SIGUSR1:
            strcpy(str, "USR1");
            break;
        case SIGUSR2:
            strcpy(str, "USR2");
            break;
        default:
            strcpy(str, "UNKNOWN");
            return -1;
    }
    return 0;
}
