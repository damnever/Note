#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
 * Fork a child process and create a session.
 * Child process become leader of process group and no controlling terminal.
 */

int
main(void)
{
    pid_t child_id, sid;

    if ((child_id = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (child_id == 0) {  // child
        if ((sid = setsid()) < 0) {
            fprintf(stderr, "setsid error\n");
            exit(1);
        }
        printf("Is leader ? %s.\n", sid == (pid_t)getpid() ? "True" : "False");
        printf("Has%s controlling terminal.\n", open("/dev/tty", O_RDONLY) < 0 ? " not" : "");
        exit(0);
    }

    if (waitpid(child_id, NULL, 0) != child_id) {
        fprintf(stderr, "waitpid error\n");
        exit(1);
    }

    exit(0);
}
