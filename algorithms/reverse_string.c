/*
 * https://leetcode.com/problems/reverse-string/
 */

#include <stdio.h>
#include <string.h>


char * reverse_string(char *s);

int
main() {
    char s[] = "hello";
    char s1[] = "wt";

    printf("%s ->", s);
    printf(" %s\n", reverse_string(s));
    printf("%s ->", s1);
    printf(" %s\n", reverse_string(s1));

    return 0;
}

// in place
char *
reverse_string(char *s)
{
    char *bp, *ep, tmp;
    int len = strlen(s);

    if (len == 0) return s;
    for (bp = s, ep = s + len - 1; bp < ep; ++bp, --ep) {
        tmp = *bp;
        *bp = *ep;
        *ep = tmp;
    }

    return s;
}
