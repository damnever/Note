// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
    int max = 0;
    int len = 0;
    int ht[137] = {0}; // printable characters(176 - 40 + 1): https://en.wikipedia.org/wiki/ASCII
    char *lp, *rp;
    lp = rp = s;

    for (;*rp != '\0';) {
        int i = *rp - ' ';
        if (ht[i] == 1) {
            if ((len = rp - lp) > max) {
                max = len;
            }
            for (;*lp != *rp;) { // find the repeat character
                i = *lp - ' ';
                ht[i] = 0; // clear mark
                lp += 1;
            }
            if (lp != rp) { // not in the same position, then move the left forward
                lp += 1;
            }
        } else {
            ht[i] = 1; // mark
        }
        rp += 1;
    }

    if ((len = rp - lp) > max) {
        max = len;
    }
    return max;
}

int main()
{
    printf(": %d\n", lengthOfLongestSubstring(""));
    printf("abcabcbb: %d\n", lengthOfLongestSubstring("abcabcbb"));
    printf("bbbbb: %d\n", lengthOfLongestSubstring("bbbbb"));
    printf("pwwkew: %d\n", lengthOfLongestSubstring("pwwkew"));
    return 0;
}
