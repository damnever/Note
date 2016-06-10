#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct _stack_t {
    void *elements;
    int elem_size;
    int cap;
    int len;
} Stack;

Stack * stack_new(int cap, int elem_size);
bool stack_push(Stack *stack, const void *val_addr);
bool stack_pop(Stack *stack, void *val_addr);
bool stack_top(Stack *stack, void *val_addr);
bool stack_is_empty(Stack *stack);
void stack_free(Stack *stack);

#endif
