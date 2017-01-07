/* https://leetcode.com/problems/find-the-difference/
 */

#include <stdio.h>

char findTheDifference(char* s, char* t)
{
    char *sp, *tp;
    int sc, tc;

    sp = s;
    tp = t;
    sc = tc = 0;
    for (; *tp != 0; tp++) {
        tc += *tp - '0';
        if (*sp != 0) {
            sc += *sp - '0';
            sp++;
        }
    }

    return (tc-sc) + '0';
}

int main()
{
    printf("%c\n", findTheDifference("abcd", "abcde"));
    printf("%c\n", findTheDifference("abcd", "abedc"));

    return 0;
}
