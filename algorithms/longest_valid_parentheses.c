/*
 * https://leetcode.com/problems/longest-valid-parentheses/description/
 */

#include <stdio.h>
#include "../cutils/stack.h"

typedef struct _selem {
    char ch;
    int idx;
} selem;

int longestValidParentheses(char* s) {
    char *sp;
    selem se;
    int c = -1, max = 0, tmp;
    bool notempty = false;
    Stack *stack = stack_new(sizeof(selem*));

    for (sp = s; *sp != '\0'; sp++) {
        c++;
        if ((notempty = stack_peek(stack, &se)) && *sp == ')' && se.ch == '(') {
            stack_pop(stack, &se);
            if ((notempty = stack_peek(stack, &se))) {
                if ((tmp = c - se.idx) > max) max = tmp;
            } else {
                if (c >= max) max = c + 1;
            }
        } else {
            selem tmpse = {.ch = *sp, .idx = c};
            stack_push(stack, &tmpse);
        }
    }

    stack_free(stack);
    return max;
}

int main()
{
    printf("%d\n", longestValidParentheses("(()(())"));
    printf("%d\n", longestValidParentheses("()()(()"));
    return 0;
}
