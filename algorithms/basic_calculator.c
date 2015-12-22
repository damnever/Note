#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
 * https://leetcode.com/problems/basic-calculator/
 */

char *
reverse_polish_notation(char *s, int size)
{
    int i, len, top;
    char operators[size * 2], expression[size * 2];
    char *exp = expression, *notations;

    top = 0;
    for (i = 0; i < size;) {
        switch (s[i]) {
            case '(':
                operators[top++] = s[i++];
                break;
            case ')':
                while (top != 0 && operators[top - 1] != '(') {
                    *(exp++) = operators[--top];
                }
                top -= 1;
                i += 1;
                break;
            case '+':
            case '-':
                while (top != 0 && operators[top - 1] != '(') {
                    *(exp++) = operators[--top];
                }
                operators[top++] = s[i++];
                break;
            case ' ':
                i += 1;
                break;
            default:
                while (s[i] >= '0' && s[i] <= '9') {
                    *(exp++) = s[i++];
                }
                *(exp++) = ',';
                break;
        }
    }

    while (top != 0) {
        if (operators[top - 1] == '(' || operators[top - 1] == '(') {
            top -= 1;
            continue;
        }
        *(exp++) = operators[--top];
    }
    *(exp++) = '$';
    *exp = '\0';

    len = strlen(expression) + 1;
    notations = (char *)malloc(len * sizeof(char));
    memset(notations, 0, len * sizeof(char));
    strcpy(notations, expression);

    return notations;
}

int
calculate(char *s)
{
    char *notations, *bp;
    int num, top, size = strlen(s);
    int stack[size];

    notations = reverse_polish_notation(s, size);
    bp = notations;
    top = 0;

    while (*bp != '$') {
        switch (*bp) {
            case '+':
                stack[top - 2] += stack[top - 1];
                top -= 1;
                break;
            case '-':
                stack[top - 2] -= stack[top - 1];
                top -= 1;
                break;
            default:
                num = 0;
                while (*bp >= '0' && *bp <= '9') {
                    num = 10 * num + *bp - '0';
                    bp++;
                }
                stack[top++] = num;
                break;
        }
        bp++;
    }

    free(notations);

    return stack[0];
}

int
main()
{
    char *str = "(1-(2+3)+(4+5))-5";
    printf("%s = %d\n", str, calculate(str));

    return 0;
}
