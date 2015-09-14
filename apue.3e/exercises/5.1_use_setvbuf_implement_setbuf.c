#include <stdio.h>

/*
 * If `buf` is NULL, close buffer,
 * if `fp` is stderr, no buffer,
 * if `fp` is stdin or stdout, line buffer,
 * otherwise, full buffer.
 */

void
my_setbuf(FILE *fp, char *buf)
{
    int mode;

    if (NULL == buf || stderr == fp) {
        mode = _IONBF;
    } else if (stdin == fp || stdout == fp) {
        mode = _IOLBF;
    } else {
        mode = _IOFBF;
    }

    if (setvbuf(fp, buf, mode, BUFSIZ) != 0) {
        fprintf(stderr, "setvbuf error!\n");
        return;
    }
}


/* Code borrow from apue.3e P164 Pic5-11 */
#if defined(_IO_UNBUFFERED)

int
is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IO_UNBUFFERED);
}

int
is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IO_LINE_BUF);
}

#elif defined(__SNBF)

int
is_unbuffered(FILE *fp)
{
    return (fp->_flags & __SNBF);
}

int
is_linebuffered(FILE *fp)
{
    return (fp->_flags & __SLBUF);
}

#elif defined(_IONBF)

#ifdef _LP64
#define _flag __pad[4]
#endif

int
is_unbuffered(FILE *fp)
{
    return (fp->_flag & _IONBF);
}

int
is_linebuffered(FILE *fp)
{
    return (fp->_flag & _IOLBF);
}

#else

#error unknown stdio implementation!

#endif

void
pr_stdio(FILE *fp)
{
    if (is_unbuffered(fp))
        printf("unbuffered\n");
    else if (is_linebuffered(fp))
        printf("linebuffered\n");
    else
        printf("fullbuffered\n");
}

int
main()
{
    FILE *fp;
    char buf[BUFSIZ];

    my_setbuf(stderr, buf);
    pr_stdio(stderr);

    my_setbuf(stdout, buf);
    pr_stdio(stdout);

    fp = fopen("./3.2_implement_dup2.c", "r");
    my_setbuf(fp, buf);
    pr_stdio(fp);

    my_setbuf(fp, NULL);
    pr_stdio(fp);

    return 0;
}
