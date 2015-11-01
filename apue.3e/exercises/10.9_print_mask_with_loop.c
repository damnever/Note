#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

// Kernel: 3.13.0-66-generic /usr/include/bits/signum.h
const char *sig_no_name[] = {
    "SIGHUP",
    "SIGINT",
    "SIGQUIT",
    "SIGILL",
    "SIGTRAP",
#ifdef SIGIOT
    "SIGIOT",
#else
    "SIGABRT",
#endif
    "SIGBUS",
    "SIGFPE",
    "SIGKILL",
    "SIGUSR1",
    "SIGSEGV",
    "SIGUSR2",
    "SIGPIPE",
    "SIGALRM",
    "SIGTERM",
    "SIGSTKFLT",
#ifdef SIGCLD
    "SIGCLD",
#else
    "SIGCHLD",
#endif
    "SIGCONT",
    "SIGSTOP",
    "SIGTSTP",
    "SIGTTIN",
    "SIGTTOU",
    "SIGURG",
    "SIGXCPU",
    "SIGXFSZ",
    "SIGVTALRM",
    "SIGPROF",
    "SIGWINCH",
#ifdef SIGPOLL
    "SIGPOLL",
#else
    "SIGIO",
#endif
    "SIGPWR",
    "SIGSYS"
};

void pr_mask(const char *str);


int
main()
{
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGALRM);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGUSR2);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
    pr_mask("XXX: ");

    return 0;
}

void
pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;
    int signo;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        fprintf(stderr, "sigprocmask error. %s\n", errno != 0 ? strerror(errno) : "");
    } else {
        printf("%s", str);
        for (signo = 1; signo < NSIG; ++signo) {
            if (sigismember(&sigset, signo)) {
                printf(" %s", sig_no_name[signo - 1]);
            }
        }
        printf("\n");
    }

    errno = errno_save;
}
