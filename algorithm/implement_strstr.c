#include <stdio.h>

/* https://leetcode.com/problems/implement-strstr/
 */

int str_str(char *haystack, char *needle);


int main()
{
    printf("%d\n", str_str("abcdef", "cde"));
    printf("%d\n", str_str("adbc", "adc"));
    printf("%d\n", str_str("", ""));
    return 0;
}

int str_str(char *haystack, char *needle)
{
    int idx = 0;
    char *lh, *rh, *bn;

    if('\0' == *needle) return 0;

    lh = haystack;
    while(*lh){
        bn = needle;
        rh = lh;
        while(*rh && *bn && *rh == *bn){
            rh++;
            bn++;
        }
        if('\0' == *bn || '\0' == *rh) break;
        lh++;
        idx++;
    }

    return '\0' == *bn ? idx : -1;
}
