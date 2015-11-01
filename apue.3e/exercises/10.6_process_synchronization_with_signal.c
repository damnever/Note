#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define FILE_PATH "./test.txt"
#define NUM 12
#define NUM_LEN 2

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

int read_num(const char *fpath);
void write_num(const char *fpath, int num);
void err_msg(const char *fmt, ...);
static void sig_usr(int signo);
void TELL_WAIT(void);
void TELL_PARENT(pid_t pid);
void WAIT_PARENT(void);
void TELL_CHILD(pid_t pid);
void WAIT_CHILD(void);


int
main()
{
    pid_t pid;
    int num;

    num = 0;
    write_num(FILE_PATH, num);
    setbuf(stdout, NULL);

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_msg("fork error");
    } else if (pid == 0) {  // child
        TELL_PARENT(getppid());  // parent go first

        while (num < NUM) {
            WAIT_PARENT();
            if ((num = read_num(FILE_PATH)) < NUM) {
                num += 1;
                write_num(FILE_PATH, num);
                printf("Child (%d) write: %d\n", getpid(), num);
            }
            TELL_PARENT(getppid());
        }
        exit(0);
    } else {  // parent
        while (num < NUM) {
            WAIT_CHILD();
            if ((num = read_num(FILE_PATH)) < NUM) {
                num += 1;
                write_num(FILE_PATH, num);
                printf("Parent (%d) write: %d\n", getpid(), num);
            }
            TELL_CHILD(pid);
        }
    }

    if (waitpid(pid, NULL, 0) != pid) {
        err_msg("waitpid error");
    }

    return 0;
}

int
read_num(const char *fpath)
{
    FILE *fp;
    char content[NUM_LEN];

    if ((fp = fopen(fpath, "rb")) == NULL) {
        err_msg("fopen error");
    }

    if (fread(content, 1, NUM_LEN, fp) <= 0) {
        err_msg("fread error");
    }

    return atoi(content);
}

void
write_num(const char *fpath, int num)
{
    FILE *fp;
    char content[NUM_LEN];

    sprintf(content, "%d", num);
    if ((fp = fopen(fpath, "wb")) == NULL) {
        err_msg("fopen error");
    }

    if (fwrite(content, 1, strlen(content), fp) != strlen(content)) {
        err_msg("fwrite error");
    }

    if (fclose(fp) == EOF) {
        err_msg("fclose error");
    }
}

void
err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, fmt, ap);
    if (errno) {
        fprintf(stderr, ": %d %s", errno, strerror(errno));
    }
    fprintf(stderr, "\n");
    va_end(ap);

    exit(1);
}

/* Code borrow from apue.3e Figure-10.24 */
static void
sig_usr(int signo)
{
    sigflag = 1;
}

void
TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        err_msg("signal(SIGUSR1) error");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        err_msg("singal(SIGUSR2) error");
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        err_msg("SIG_BLOCK error");
    }
}

void
TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}

void
WAIT_PARENT(void)
{
    while (sigflag == 0) {
        sigsuspend(&zeromask);
    }
    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_msg("SIG_SETMASK error");
    }
}

void
TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);
}

void
WAIT_CHILD(void)
{
    while (sigflag == 0) {
        sigsuspend(&zeromask);
    }
    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_msg("SIG_SETMASK error");
    }
}
