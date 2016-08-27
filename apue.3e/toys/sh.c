#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>

// Simplifed xv6 shell.

#define MAXARGS 10
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define EXIT_IF_ERR(failed, msg) ({  \
        if ((failed)) {  \
            fprintf(stderr, "(%s:%s:%d) %s error: %s\n",  \
                    __FILE__, __func__, __LINE__,  \
                    msg, errno > 0 ? strerror(errno) : "unknown");  \
            exit(1);  \
        }  \
    })
#define CLOSE(fd) EXIT_IF_ERR( (close(fd) < 0), "close" )
#define OPEN(fpath, mode) EXIT_IF_ERR( ((open(fpath, mode, FILE_MODE)) < 0), "open" )
#define DUP(fd) EXIT_IF_ERR( (dup(fd) < 0), "dup" )
#define DUP2(fd, fd2) EXIT_IF_ERR( (dup2(fd, fd2) < 0), "dup2" )

// All commands have at least a type. Have looked at the type, the code
// typically casts the *cmd to some specific cmd type.
struct cmd {
    int type;                    //  ' ' (exec), | (pipe), '<' or '>' for redirection
};

struct execcmd {
    int type;                            // ' '
    int argc;
    char *argv[MAXARGS];     // arguments to the command to be exec-ed
};

struct redircmd {
    int type;                    // < or >
    struct cmd *cmd;     // the command to be run (e.g., an execcmd)
    char *file;              // the input/output file
    int mode;                    // the mode to open the file with
    int fd;                      // the file descriptor number to use for the file
};

struct pipecmd {
    int type;                    // |
    struct cmd *left;  // left side of pipe
    struct cmd *right; // right side of pipe
};

int fork1(void);    // Fork but exits on failure.
struct cmd *parsecmd(char*);
void exec_cmd(struct execcmd *cmd);
void exec_pcmd(struct pipecmd *cmd);
void exec_rcmd(struct redircmd *cmd);

// Execute cmd.  Never returns.
void
runcmd(struct cmd *cmd)
{
    struct execcmd *ecmd;
    struct pipecmd *pcmd;
    struct redircmd *rcmd;

    if(cmd == 0)
        exit(0);

    switch(cmd->type){
    default:
        fprintf(stderr, "unknown runcmd\n");
        exit(-1);

    case ' ':
        ecmd = (struct execcmd*)cmd;
        if(ecmd->argv[0] == 0)
            exit(0);
        /* fprintf(stderr, "exec not implemented\n"); */
        // Your code here ...
        exec_cmd(ecmd);
        break;

    case '>':
    case '<':
        rcmd = (struct redircmd*)cmd;
        /* fprintf(stderr, "redir not implemented\n"); */
        // Your code here ...
        exec_rcmd(rcmd);
        break;

    case '|':
        pcmd = (struct pipecmd*)cmd;
        /* fprintf(stderr, "pipe not implemented\n"); */
        // Your code here ...
        exec_pcmd(pcmd);
        break;
    }
    exit(0);
}

/* execute cmds */

void
exec_cmd(struct execcmd *cmd)
{
    if (cmd->argc == 0) return;
    // execv need absolute pathname, but execvp will search $PATH
    EXIT_IF_ERR( (execvp(cmd->argv[0], cmd->argv) < 0), cmd->argv[0] );
}

void
exec_pcmd(struct pipecmd *cmd)
{
    int pid1, pid2, p[2];

    EXIT_IF_ERR( (pipe(p) < 0), "pipe");

    pid1 = fork1();
    if (pid1 == 0) {  // child
        CLOSE(1);
        DUP(p[1]);
        CLOSE(p[0]);
        CLOSE(p[1]);
        runcmd((struct cmd*)cmd->left);
    }

    pid2 = fork1();
    if (pid2 == 0) {
        CLOSE(0);
        DUP(p[0]);
        CLOSE(p[0]);
        CLOSE(p[1]);
        runcmd((struct cmd*)cmd->right);
    }

    CLOSE(p[0]);
    CLOSE(p[1]);
    EXIT_IF_ERR( waitpid(pid1, NULL, 0) < 0, "waitpid");
    EXIT_IF_ERR( waitpid(pid2, NULL, 0) < 0, "waitpid");
}

void
exec_rcmd(struct redircmd *cmd)
{
    CLOSE(cmd->fd);
    OPEN(cmd->file, cmd->mode);
    runcmd(cmd->cmd);
}

int
getcmd(char *buf, int nbuf)
{
    if (isatty(fileno(stdin)))
        fprintf(stdout, "6.828$ ");
    memset(buf, 0, nbuf);
    fgets(buf, nbuf, stdin);
    if(buf[0] == 0) // EOF
        return -1;
    return 0;
}

int
main(void)
{
    static char buf[100];
    int r;

    // Read and run input commands.
    while(getcmd(buf, sizeof(buf)) >= 0){
        if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
            // Clumsy but will have to do for now.
            // Chdir has no effect on the parent if run in the child.
            buf[strlen(buf)-1] = 0;  // chop \n
            if(chdir(buf+3) < 0)
                fprintf(stderr, "cannot cd %s\n", buf+3);
            continue;
        }
        if(fork1() == 0)
            runcmd(parsecmd(buf));
        wait(&r);
    }
    exit(0);
}

int
fork1(void)
{
    int pid;

    pid = fork();
    EXIT_IF_ERR( pid < 0, "fork");
    return pid;
}

struct cmd*
execcmd(void)
{
    struct execcmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = ' ';
    cmd->argc = 0;
    return (struct cmd*)cmd;
}

struct cmd*
redircmd(struct cmd *subcmd, char *file, int type)
{
    struct redircmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = type;
    cmd->cmd = subcmd;
    cmd->file = file;
    cmd->mode = (type == '<') ?  O_RDONLY : O_WRONLY|O_CREAT|O_TRUNC;
    cmd->fd = (type == '<') ? 0 : 1;
    return (struct cmd*)cmd;
}

struct cmd*
pipecmd(struct cmd *left, struct cmd *right)
{
    struct pipecmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = '|';
    cmd->left = left;
    cmd->right = right;
    return (struct cmd*)cmd;
}

// Parsing

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>";

int
gettoken(char **ps, char *es, char **q, char **eq)
{
    char *s;
    int ret;

    s = *ps;
    while(s < es && strchr(whitespace, *s))
        s++;
    if(q)
        *q = s;
    ret = *s;
    switch(*s){
    case 0:
        break;
    case '|':
    case '<':
        s++;
        break;
    case '>':
        s++;
        break;
    default:
        ret = 'a';
        while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
            s++;
        break;
    }
    if(eq)
        *eq = s;

    while(s < es && strchr(whitespace, *s))
        s++;
    *ps = s;
    return ret;
}

int
peek(char **ps, char *es, char *toks)
{
    char *s;

    s = *ps;
    while(s < es && strchr(whitespace, *s))
        s++;
    *ps = s;
    return *s && strchr(toks, *s);
}

struct cmd *parseline(char**, char*);
struct cmd *parsepipe(char**, char*);
struct cmd *parseexec(char**, char*);

// make a copy of the characters in the input buffer, starting from s through es.
// null-terminate the copy to make it a string.
char
*mkcopy(char *s, char *es)
{
    int n = es - s;
    char *c = malloc(n+1);
    assert(c);
    strncpy(c, s, n);
    c[n] = 0;
    return c;
}

struct cmd*
parsecmd(char *s)
{
    char *es;
    struct cmd *cmd;

    es = s + strlen(s);
    cmd = parseline(&s, es);
    peek(&s, es, "");
    if(s != es){
        fprintf(stderr, "leftovers: %s\n", s);
        exit(-1);
    }
    return cmd;
}

struct cmd*
parseline(char **ps, char *es)
{
    struct cmd *cmd;
    cmd = parsepipe(ps, es);
    return cmd;
}

struct cmd*
parsepipe(char **ps, char *es)
{
    struct cmd *cmd;

    cmd = parseexec(ps, es);
    if(peek(ps, es, "|")){
        gettoken(ps, es, 0, 0);
        cmd = pipecmd(cmd, parsepipe(ps, es));
    }
    return cmd;
}

struct cmd*
parseredirs(struct cmd *cmd, char **ps, char *es)
{
    int tok;
    char *q, *eq;

    while(peek(ps, es, "<>")){
        tok = gettoken(ps, es, 0, 0);
        if(gettoken(ps, es, &q, &eq) != 'a') {
            fprintf(stderr, "missing file for redirection\n");
            exit(-1);
        }
        switch(tok){
        case '<':
            cmd = redircmd(cmd, mkcopy(q, eq), '<');
            break;
        case '>':
            cmd = redircmd(cmd, mkcopy(q, eq), '>');
            break;
        }
    }
    return cmd;
}

struct cmd*
parseexec(char **ps, char *es)
{
    char *q, *eq;
    int tok, argc;
    struct execcmd *cmd;
    struct cmd *ret;

    ret = execcmd();
    cmd = (struct execcmd*)ret;

    argc = 0;
    ret = parseredirs(ret, ps, es);
    while(!peek(ps, es, "|")){
        if((tok=gettoken(ps, es, &q, &eq)) == 0)
            break;
        if(tok != 'a') {
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        cmd->argv[argc] = mkcopy(q, eq);
        argc++;
        if(argc >= MAXARGS) {
            fprintf(stderr, "too many args\n");
            exit(-1);
        }
        ret = parseredirs(ret, ps, es);
    }
    cmd->argc = argc;
    cmd->argv[argc] = 0;
    return ret;
}
