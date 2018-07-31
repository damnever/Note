// https://leetcode.com/problems/valid-palindrome/description/

#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(char* s)
{
    int i = 0, sp = 0, n = 0, o;
    char c;
    char ooops[131072] = {0};  // 128K.. the size matters..

    // XXX(damnever): Maybe without the copy is even faster.. so be it..
    for (; *s != '\0'; s += 1) {
        n += 1;
        if (*s == ' ') {
            sp += 1;
            continue;
        }

        if (*s >= '0' && *s <= '9') { // num
            ooops[i++] = *s;
            continue;
        }
        // alphabet
        o = *s - 'a';
        c = *s;
        if (o >= -32 && o <= -7) {  // uppercase
            o += 32;
            c = o + 'a';
        }
        if (o >= 0 && o <= 25) {
            ooops[i++] = c;
        }
    }

    if (n == sp) { return true; }

    ooops[i] = '\0';
    n = i % 2 != 0 ? (i/2)+1 : i/2;
    char *b = ooops;
    char *e = ooops + i - 1;

    for (; n > 0; n--) {
        if (*e != *b) {
            return false;
        }
        e -= 1;
        b += 1;
    }
    return true;
}

int main()
{
    printf("%s\n", isPalindrome("a.") ? "true" : "false");
    printf("%s\n", isPalindrome("0P") ? "true" : "false");
    printf("%s\n", isPalindrome("A man, a plan, a canal: Panama") ? "true" : "false");
    printf("%s\n", isPalindrome("race a car") ? "true" : "false");
    return 0;
}
