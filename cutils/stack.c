/** A simple generic type stack.
 *
 * Example usage:
 *   int i, tmp,  max = 6;
 *   Stack *s = stack_new(sizeof(int));
 *   for (i = 0; i < max; ++i) {
 *       stack_push(s, &i);
 *   }
 *   for (i = 0; i < max; ++i) {
 *       stack_pop(s, &tmp);
 *       printf("%d ", tmp);
 *   }
 *   printf("\n");
**/

#include "stack.h"


Stack *
stack_new(int elem_size)
{
    Stack *stack;

    if ( (stack = ((Stack *)malloc(sizeof(Stack)))) == NULL ) {
        return NULL;
    }
    if ( (stack->elements = malloc(elem_size * INIT_STACK_CAP)) == NULL ) {
        free(stack);
        stack = NULL;
        return NULL;
    }
    stack->elem_size = elem_size;
    stack->cap = INIT_STACK_CAP;
    stack->len = 0;

    return stack;
}

bool
stack_push(Stack *stack, const void *val_addr)
{
    assert(stack != NULL);
    char *to_addr;

    if (stack->len >= stack->cap) {
        stack->cap *= 2;
        stack->elements = realloc(stack->elements, stack->elem_size * stack->cap);
        if (stack->elements == NULL) return false;
    }

    to_addr = (char *)stack->elements + stack->elem_size * stack->len;
    memcpy(to_addr, val_addr, stack->elem_size);
    stack->len += 1;

    return true;
}

bool
stack_pop(Stack *stack, void *val_addr)
{
    assert(stack != NULL);

    if (stack->len <= 0) return false;
    stack_peek(stack, val_addr);
    stack->len -= 1;

    return true;
}

bool
stack_peek(Stack *stack, void *val_addr)
{
    assert(stack != NULL);
    char *addr;

    if (stack->len <= 0) return false;
    addr = (char *)stack->elements + stack->elem_size * (stack->len-1);
    memcpy(val_addr, addr, stack->elem_size);

    return true;
}

bool
stack_is_empty(Stack *stack)
{
    assert(stack != NULL);
    return (stack->len == 0);
}

int
stack_size(Stack *stack)
{
    assert(stack != NULL);
    return stack->len;
}

void
stack_free(Stack *stack)
{
    assert(stack != NULL);
    free(stack->elements);
    free(stack);
    stack = NULL;
}
