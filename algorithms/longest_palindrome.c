// https://leetcode.com/problems/longest-palindrome/description/

#include <stdio.h>


int longestPalindrome(char* s)
{
    int ht[58] = {0}; // 'z' - 'A'
    int n = 0;
    int pair = 0;
    for (; *s != '\0';) {
        int ord = *s - 'A';
        if (ht[ord] != 0) {
            ht[ord] = 0;
            pair += 1;
            n -= 1;
        } else {
            ht[ord] = 1;
            n += 1;
        }
        s++;
    }
    return n == 0 ? (pair * 2) : (pair*2 + 1);
}

int main()
{
    printf("abccccdd: %d\n", longestPalindrome("abccccdd"));
    return 0;
}
