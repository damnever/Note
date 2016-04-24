/*
 * https://leetcode.com/problems/reverse-vowels-of-a-string/
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


bool is_vowels(char);

char *reverse_vowels(char *s)
{
    int left, right;
    bool lv, rv;
    int len = strlen(s);
    char *rs = (char *)malloc(len);

    memset(rs, 0, len);
    left = 0, right = len - 1;
    lv = false, rv = false;

    for (; left < right;) {
        lv = is_vowels(s[left]);
        rv = is_vowels(s[right]);

        if (lv && rv) {
            rs[left] = s[right];
            rs[right] = s[left];
            left += 1;
            right -= 1;
        } else {
            if (!lv) {
                rs[left] = s[left];
                left += 1;
            }
            if (!rv) {
                rs[right] = s[right];
                right -= 1;
            }
        }
    }
    // left a single vowel.
    if (left == right) {
        rs[left] = s[left];
    }

    return rs;
}

bool is_vowels(char c)
{
    switch (c) {
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':
            return true;
    }
    return false;
}

int main()
{
    char s[] = "leetcode";
    char s1[] = "a.";
    char s2[] = " ";
    char *rs = reverse_vowels(s);
    char *rs1 = reverse_vowels(s1);
    char *rs2 = reverse_vowels(s2);

    printf("%s => %s\n", s, rs);
    printf("%s => %s\n", s1, rs1);
    printf("%s => %s|\n", s2, rs2);

    free(rs);
    free(rs1);
    free(rs2);

    return 0;
}
