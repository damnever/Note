#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct _queue_node_t {
    void *val;
    struct _queue_node_t *next;
} QNode;

typedef struct _queue_t {
    QNode *head;
    QNode *tail;
    int len;
    int elem_size;
} Queue;

Queue * queue_new(int elem_size);
bool queue_append(Queue *queue, const void *val_addr);
bool queue_remove(Queue *queue, void *val_addr);
bool queue_is_empty(Queue *queue);
int queue_size(Queue *queue);
void queue_free(Queue *queue);

#endif
