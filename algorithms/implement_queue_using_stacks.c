#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * https://leetcode.com/problems/implement-queue-using-stacks/
 * You may assume that all operations are valid (for example,
 * no pop or peek operations will be called on an empty queue).
 * So, fuck it...
 */

typedef struct {
    int *current;
    int *stack1;
    int *stack2;
    int top1;
    int top2;
    int count;
    int got;
} Queue;

/* Create a queue */
void
queueCreate(Queue *queue, int maxSize)
{
    queue->stack1 = (int *)malloc(maxSize * sizeof(int));
    queue->stack2 = (int *)malloc(maxSize * sizeof(int));
    queue->top1 = 0;
    queue->top2 = 0;
    queue->count = 0;
    queue->current = queue->stack1;
    queue->got = 0;
}

/* Push element x to the back of queue */
void
queuePush(Queue *queue, int element)
{
    int *tmp, top;
    if(0 == queue->got) {
        if(queue->current == queue->stack1) {
            queue->stack1[queue->top1++] = element;
            queue->count = queue->top1;
        } else {
            queue->stack2[queue->top2++] = element;
            queue->count = queue->top2;
        }
        return;
    }
    if(queue->current == queue->stack1) {
        tmp = queue->stack1;
        top = queue->top1;
        queue->current = queue->stack2;
        queue->top2 = top + 1;
        queue->top1 = 0;
    } else {
        tmp = queue->stack2;
        top = queue->top2;
        queue->current = queue->stack1;
        queue->top1 = top + 1;
        queue->top2 = 0;
    }
    --top;
    queue->count = 0;
    for(; top >=0; top--) {
        queue->current[queue->count++] = tmp[top];
    }
    queue->current[queue->count++] = element;
    queue->got = 0;
}

/* Removes the element from front of queue */
void
queuePop(Queue *queue)
{
    int *tmp, top;
    if(1 == queue->got) {
        if(queue->current == queue->stack1) {
            --queue->top1;
        } else {
            --queue->top2;
        }
        --queue->count;
        return;
    }
    if(queue->current == queue->stack1) {
        tmp = queue->stack1;
        top = queue->top1;
        queue->current = queue->stack2;
        queue->top2 = top - 1;
        queue->top1 = 0;
    } else {
        tmp = queue->stack2;
        top = queue->top2;
        queue->current = queue->stack1;
        queue->top1 = top - 1;
        queue->top2 = 0;
    }
    --top;
    queue->count = 0;
    for(; top >=0; top--) {
        queue->current[queue->count++] = tmp[top];
    }
    --queue->count;
    queue->got = 1;
}

/* Get the front element */
int
queuePeek(Queue *queue)
{
    int *tmp, top;
    if(1 == queue->got) {
        return queue->current[queue->count - 1];
    }
    if(queue->current == queue->stack1) {
        tmp = queue->stack1;
        top = queue->top1;
        queue->current = queue->stack2;
        queue->top1 = 0;
        queue->top2 = top;
    } else {
        tmp = queue->stack2;
        top = queue->top2;
        queue->current = queue->stack1;
        queue->top2 = 0;
        queue->top1 = top;
    }
    --top;
    queue->count = 0;
    for(; top >=0; top--) {
        queue->current[queue->count++] = tmp[top];
    }
    queue->got = 1;
    return queue->current[queue->count - 1];
}

/* Return whether the queue is empty */
bool
queueEmpty(Queue *queue)
{
    return queue->count == 0 ? true : false;
}

/* Destroy the queue */
void
queueDestroy(Queue *queue)
{
    queue->count = 0;
    queue->top1 = 0;
    queue->top2 = 0;
    free(queue->stack1);
    queue->stack1 = NULL;
    free(queue->stack2);
    queue->stack2 = NULL;
    queue->current = NULL;
}

int
main()
{
    Queue queue;
    queueCreate(&queue, 5);
    queuePush(&queue, 1);
    queuePush(&queue, 2);
    queuePop(&queue);
    printf("%d\n", queuePeek(&queue));

    queuePop(&queue);
    queuePush(&queue, 1);
    queuePush(&queue, 2);
    printf("%d\n", queuePeek(&queue));
    queuePush(&queue, 3);
    printf("%d\n", queuePeek(&queue));
    printf("%d\n", queuePeek(&queue));

    queueDestroy(&queue);
    return 0;
}
