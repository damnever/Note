#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* https://leetcode.com/problems/valid-parentheses/
 * I implement a stack, which hash variable size.
 */

typedef struct stack_ {
    char *data;
    int size;
    int top;
} Stack;

bool is_valid(char *s);
// Stack, has a variable size;
void stack_init(Stack *stack);
void stack_push(Stack *stack, char elem);
char stack_pop(Stack *stack);
void stack_destroy(Stack *stack);
int stack_count(Stack *stack);


int main()
{
    printf("%d\n", is_valid("(){}"));
    printf("%d\n", is_valid("(["));
    return 0;
}

bool is_valid(char *s)
{
    bool valid = true;
    Stack stack;
    if(')' == *s || ']' == *s || ']' == *s)
        return false;

    stack_init(&stack);
    while(*s){
        switch(*s){
            case '(':
            case '[':
            case '{':
                stack_push(&stack, *s);
                break;
            case ')':
                if('(' != stack_pop(&stack)) {
                    valid = false;
                }
                break;
            case ']':
                if('[' != stack_pop(&stack)) {
                    valid = false;
                }
                break;
            case '}':
                if('{' != stack_pop(&stack)) {
                    valid = false;
                }
                break;
            default:
                valid = false;
                break;
        }
        if(!valid) break;
        s++;
    }
    if(stack_count(&stack) > 0){
        valid = false;
    }
    stack_destroy(&stack);
    return valid;
}

//
// Stack.
//
void stack_init(Stack *stack)
{
    stack->size = 10;
    stack->top = 0;
    stack->data = (char *)malloc(stack->size * sizeof(char));
}

void stack_push(Stack *stack, char elem)
{
    if(NULL == stack->data)
        return;
    if(stack->top >= stack->size){
        stack->size *= 2;
        stack->data = (char *)realloc(stack->data, stack->size * sizeof(char));
    }
    stack->data[stack->top++] = elem;
}

char stack_pop(Stack *stack)
{
    if(NULL == stack->data || 0 == stack->top)
        return '\0';
    return stack->data[--stack->top];
}

void stack_destroy(Stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->top = 0;
}

int stack_count(Stack *stack)
{
    return stack->top;
}
