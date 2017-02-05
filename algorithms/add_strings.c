/*
 * https://leetcode.com/problems/add-strings/
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
addStrings(char *num1, char *num2)
{
    int c, n = 5101;
    char arr[n], tmp[2];
    char *p1, *p2, *res;

    c = 0;
    for (p1 = num1 + strlen(num1)-1, p2 = num2 + strlen(num2)-1;
            *p1 != 0 || *p2 != 0;) {
        int n1 = 0, n2 = 0;
        if (*p1 != 0) {
            n1 = *p1 - '0';
            p1--;
        }
        if (*p2 != 0) {
            n2 = *p2 - '0';
            p2--;
        }
        c = c + n1 + n2;
        sprintf(tmp, "%d", c % 10);
        arr[--n] = tmp[0];
        c /= 10;
    }
    if (c != 0) {
        sprintf(tmp, "%d", c);
        arr[--n] = tmp[0];
    }

    res = (char *)malloc(5101-n+1);
    memset(res, 0, 5101-n+1);
    strncpy(res, &(arr[n]),  5101-n);
    return res;
}

int main()
{
    printf("%s\n", addStrings("8432708", "87372547"));

    printf("%s\n", addStrings("401716832807512840963",
                "167141802233061013023557397451289113296441069"));

    return 0;
}
