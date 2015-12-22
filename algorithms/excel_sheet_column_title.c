#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * https://leetcode.com/problems/excel-sheet-column-title/
 *
 * Compile with -lm
 * That's my first version, overflow...
 *  http://stackoverflow.com/questions/34416560/printfd-n-1000000001-cause-segmentation-fault
 */

char *
convertToTitle(int n)
{
    int mod, len;
    char *title, *tp;

    len = (int)(ceil(log(n) / log(26)) + 1);
    title = (char *)malloc(len * sizeof(char));
    tp = title;

    for (len -= 1; len > 0; len--) {
        tp++;
    }

    *tp = '\0';
    while (n > 26) {
        mod = n % 26;
        if (mod > 0) {
            *(--tp) = mod - 1 + 'A';
        } else if (mod == 0) {
            *(--tp) = 'Z';
            n -= 1;
        }
        n /= 26;
    }
    if (n > 0) {
        *(--tp) = n - 1 + 'A';
    }

    return title;
}

int
main()
{
    printf("%d -> %s\n", 26, convertToTitle(26));
    printf("%d -> %s\n", 30, convertToTitle(30));
    printf("%d -> %s\n", 59, convertToTitle(59));
    printf("%d -> %s\n", 52, convertToTitle(52));
    printf("%d -> %s\n", 1354, convertToTitle(1354));
    printf("%d -> %s\n", 1000000001, convertToTitle(1000000001));
    printf("%d -> %s\n", 2147483647, convertToTitle(2147483647));

    return 0;
}
