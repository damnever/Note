#include <stdio.h>

/* https://leetcode.com/problems/compare-version-numbers/
 * Support more than second level version.
 */

int compare_version(char *version1, char *version2);

int main()
{
    printf("%d\n", compare_version("01", "1"));
    printf("%d\n", compare_version("0.1", "1.1"));
    printf("%d\n", compare_version("1.1", "1.2"));
    printf("%d\n", compare_version("1.12", "1.2"));
    printf("%d\n", compare_version("1.2.3", "1.2.3"));
    return 0;
}

int compare_version(char *version1, char *version2)
{
    int v1 = 0, v2 = 0;

    while(*version1 || *version2){
        while(*version1 && '.' != *version1){
            v1 = v1 * 10 + (*version1 - '0');
            version1++;
        }
        while(*version2 && '.' != *version2){
            v2 = v2 * 10 + (*version2 - '0');
            version2++;
        }
        if(v1 > v2) {
            return 1;
        } else if (v1 < v2) {
            return -1;
        }
        if('\0' == *version1 && '\0' == *version2) break;
        v1 = 0;
        v2 = 0;
        // ignore '.'
        if (*version1) version1++;
        if (*version2) version2++;
    }
    return 0;
}
