// Boyer-Moore string search
// - http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
//
// Code is dirty...

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int boyer_moore_search(char *str, int s_len, char *pattern, int p_len);
int bad_char_offset(char *pattern, char c, int len);
int good_suffix_offset(char *pattern, char *s_last, int len);
bool starts_with(char *pattern, char *prefix, int len);
int index_of(char *str, char c, int len);

int main()
{
    int idx = 0;
    char str1[] = "HERE IS A SIMPLE EXAMPLE";
    char pattern1[] = "EXAMPLE";
    char str2[] = "I want to marry my bed";
    char pattern2[] = "marry";
    char str3[] = "bed is so cold";
    char pattern3[] = "so";

    idx = boyer_moore_search(str1, strlen(str1), pattern1, strlen(pattern1));
    printf("boyer_moore_search(\"%s\", \"%s\") = %d\n", str1, pattern1, idx);

    idx = boyer_moore_search(str2, strlen(str2), pattern2, strlen(pattern2));
    printf("boyer_moore_search(\"%s\", \"%s\") = %d\n", str2, pattern2, idx);

    idx = boyer_moore_search(str3, strlen(str3), pattern3, strlen(pattern3));
    printf("boyer_moore_search(\"%s\", \"%s\") = %d\n", str3, pattern3, idx);

    return 0;
}

int boyer_moore_search(char *str, int s_len, char *pattern, int p_len)
{
    int idx, goffset, boffset;

    for (idx = p_len - 1; idx < s_len;) {
        if (str[idx] == pattern[p_len - 1]) {
            goffset = good_suffix_offset(pattern, &str[idx], p_len);
            if (goffset == p_len) {
                break;
            } else {
                boffset = bad_char_offset(pattern, str[p_len - goffset], p_len);
                idx += goffset > boffset ? goffset : boffset;
            }
        } else {
            idx += bad_char_offset(pattern, str[idx], p_len);
        }
    }

    return idx - p_len + 1;
}

int bad_char_offset(char *pattern, char c, int len)
{
    return (len -1 - index_of(pattern, c, len));
}

int good_suffix_offset(char *pattern, char *s_last, int len)
{
    int idx, max;
    char *p_last = &pattern[len - 1];

    max = 0;
    for (idx = len; idx > 0; --idx) {
        if (*p_last == *s_last) {
            if (starts_with(pattern, p_last, len - idx + 1) && idx - 1 > max) {
                max = idx - 1;
            } else if (idx > max) {
                max = idx;
            }
            p_last--;
            s_last--;
        } else {
            break;
        }
    }
    return (idx == 0 ? len : max);
}

bool starts_with(char *pattern, char *prefix, int len)
{
    int idx;

    for (idx = 0; idx < len; ++idx) {
        if (pattern[idx] != prefix[idx]) {
            return false;
        }
    }

    return true;
}

int index_of(char *str, char c, int len)
{
    int idx;

    for (idx = 0; idx < len; ++idx) {
        if (str[idx] == c) {
            return idx;
        }
    }

    return -1;
}
