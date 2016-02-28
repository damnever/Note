#include <stdio.h>

/*
 * https://leetcode.com/problems/excel-sheet-column-number/
 */

int title_to_number(char *s);
int ch_to_number(char ch);

int main()
{
    char s[] = "A";
    char s1[] = "AA";
    char s2[] = "BCD";

    printf("%s -> %d\n", s, title_to_number(s));
    printf("%s -> %d\n", s1, title_to_number(s1));
    printf("%s -> %d\n", s2, title_to_number(s2));

    return 0;
}

int title_to_number(char *s)
{
    int number = 0;
    char *bs = s;

    number += ch_to_number(*bs);
    bs++;
    for (; *bs != '\0'; bs++) {
        number = number * 26 + ch_to_number(*bs);
    }

    return number;
}

int ch_to_number(char ch)
{
    return (ch - 'A' + 1);
}
