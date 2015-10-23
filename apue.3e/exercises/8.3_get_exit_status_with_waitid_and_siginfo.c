#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static void err_msg(const char *);
static void pr_exit(siginfo_t);

int
main(void)
{
    pid_t pid;
    int a = 1;
    siginfo_t infop;

    if ((pid = fork()) < 0) {
        err_msg("fork error\n");
    } else if (0 == pid) {
        exit(7);
    }
    if (waitid(P_PID, pid, &infop, WEXITED) < 0) {
        err_msg("waitid error\n");
    }
    pr_exit(infop);

    if ((pid = fork()) < 0) {
        err_msg("fork error\n");
    } else if (0 == pid) {
        abort();
    }
    if (waitid(P_PID, pid, &infop, WEXITED) < 0) {
        err_msg("waitid error\n");
    }
    pr_exit(infop);

    if ((pid = fork()) < 0) {
        err_msg("fork error\n");
    } else if (0 == pid) {
        a /= 0;
    }
    if (waitid(P_PID, pid, &infop, WEXITED) < 0) {
        err_msg("waitid error\n");
    }
    pr_exit(infop);

    exit(0);
}

static void
err_msg(const char *msg)
{
    fputs(msg, stderr);
    exit(1);
}

static void
pr_exit(siginfo_t infop)
{
    int sigcode = infop.si_code;
    int status = infop.si_status;
    if (CLD_EXITED == sigcode) {
        printf("normal termination, exit status = %d\n", status);
    } else if (CLD_STOPPED == sigcode) {
        printf("child stoped, signal number = %d\n", status);
    } else {
        printf("abnormal termination, signal number = %d %s\n",
                status, CLD_DUMPED == sigcode ? "(core file generated)" : "");
    }
}
