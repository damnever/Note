#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *
convert(char *s, int num_rows)
{
    int len, i, next, gap, tmp;
    char *converted, *cp;

    if (1 == num_rows) {
        return s;
    }
    len = strlen(s);
    converted = (char *)malloc(len + 1);
    memset(converted, 0, len + 1);
    cp = converted;

    gap = 2 * num_rows - 2;
    for (i = 0; i < num_rows; ++i) {
        for (next = i; next < len; next += gap) {  // col
            *cp++ = s[next];
            if (0 != i && num_rows - 1 != i) {  // Not first and last row.
                if ((tmp = (num_rows - 2 - i) + (num_rows - 1 - i) + next + 1) < len) {
                    *cp++ = s[tmp];
                }
            }
        }
    }

    return converted;
}

int
main()
{
    char *converted = NULL, *converted1 = NULL;

    converted = convert("PAYPALISHIRING", 3);
    converted1 = convert("ABCDEFGHIJKLMN", 5);
    printf("%s\n", strcmp(converted, "PAHNAPLSIIGYIR") == 0 ? "True" : "False");
    printf("%s\n", strcmp(converted1, "AIBHJCGKDFLNEM") == 0 ? "True" : "False");

    free(converted);
    free(converted1);

    return 0;
}
