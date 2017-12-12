// https://leetcode.com/problems/regular-expression-matching/description/

#include <stdio.h>
#include <stdbool.h>


bool isMatch(char *s, char *p)
{
    if (*p == '\0' && *s != '\0') return false;
    if (*p == '\0' && *s == '\0') return true;

    if (p[1] == '*') {
        char c = p[0];
        p += 2;
        do {
            if (isMatch(s, p)) return true;
        } while (*s != '\0' && (*s++ == c || c == '.'));
        return false;
    };

    if (*p != '\0' && *s == '\0') return false;
    if (*p != '.' && *p != *s) return false;
    return isMatch(s+1, p+1);
}

int main()
{
    printf("%s\n", isMatch("aa", "a") ? "true" : "false");
    printf("%s\n", isMatch("aa", "aa") ? "true" : "false");
    printf("%s\n", isMatch("aaa", "aa") ? "true" : "false");
    printf("%s\n", isMatch("aa", "a*") ? "true" : "false");
    printf("%s\n", isMatch("aa", "a.") ? "true" : "false");
    printf("%s\n", isMatch("ab", ".*") ? "true" : "false");
    printf("%s\n", isMatch("abcd", ".*") ? "true" : "false");
    printf("%s\n", isMatch("aab", "a*a*b*") ? "true" : "false");
    printf("%s\n", isMatch("aaa", "a.a") ? "true" : "false");
    printf("%s\n", isMatch("a", ".*..a*") ? "true" : "false");
    printf("%s\n", isMatch("a", "ab*") ? "true" : "false");
    return 0;
}
