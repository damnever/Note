#include <stdio.h>
#include <stdbool.h>

/*
 * https://leetcode.com/problems/valid-anagram/
 *
 * Time Limit Exceeded ...
 */

/* select sort */
void
sort(char *s)
{
    int i, max, index;
    char tmp;
    char *sp1 = s, *sp2;

    index = 0;
    while ('\0' != *sp1) {
        sp2 = sp1;
        i = index;
        max = index;
        while ('\0' != *sp2) {
            if (*sp2 > s[max]) {
                max = i;
            }
            ++i;
            ++sp2;
        }
        tmp = s[index];
        s[index] = s[max];
        s[max] = tmp;
        ++index;
        ++sp1;
    }
}

bool
is_anagram(char *s, char *t)
{
    sort(s);
    sort(t);

    while ('\0' != *s && '\0' != *t && *s == *t) {
        ++s;
        ++t;
    }

    return '\0' == *s && '\0' == *t ? true : false;
}

int
main()
{
    char s[] = "anagram";
    char t[] = "nagaram";
    char s1[] = "acac";
    char t1[] = "accc";
    char s2[] = "rat";
    char t2[] = "cat";

    printf("%d\n", is_anagram(s, t));
    printf("%d\n", is_anagram(s1, t1));
    printf("%d\n", is_anagram(s2, t2));

    return 0;
}
