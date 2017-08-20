// https://leetcode.com/problems/first-unique-character-in-a-string/description/

#include <stdio.h>

int firstUniqChar(char* s)
{
    int ht[26] = {0};
    int n = 0;
    char *sp = s;
    for (;*sp != '\0';) {
        int idx = *sp - 'a';
        ht[idx] += 1;
        sp++;
        n += 1;
    }

    for (int i = 0; i < n; i++) {
        int idx = s[i] - 'a';
        if (ht[idx] == 1) {
            return i;
        }
    }
    return -1;
}

int main()
{
    printf("leetcode: %d\n", firstUniqChar("leetcode"));
    printf("loveleetcode: %d\n", firstUniqChar("loveleetcode"));
    return 0;
}
