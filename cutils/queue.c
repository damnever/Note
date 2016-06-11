/** A simple generic queue.
 *
 * Example usage:
 *
 *   int i, val;
 *   Queue *q = queue_new(sizeof(int));
 *   for (i = 0; i < 6; ++i) queue_append(q, &i);
 *   while (!queue_is_empty(q)) {
 *       queue_remove(q, &val);
 *       printf("%d ", val);
 *   }
 *   printf("\n");
 *   queue_free(q);
 */
#include "queue.h"

QNode *q_node_new(const void *val_addr, int elem_size);
void q_node_free(QNode *qnode);

Queue *
queue_new(int elem_size)
{
    Queue *queue;

    if ( (queue = (Queue*)malloc(sizeof(Queue))) == NULL ) {
        return NULL;
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->len = 0;
    queue->elem_size = elem_size;

    return queue;
}

bool
queue_append(Queue *queue, const void *val_addr)
{
    assert(queue != NULL);
    QNode *qn;

    if (queue->head == NULL) {
        queue->head = q_node_new(val_addr, queue->elem_size);
        if (queue->head == NULL) return false;
        queue->tail = queue->head;
    } else {
        qn = q_node_new(val_addr, queue->elem_size);
        if (qn == NULL) return false;
        queue->tail->next = qn;
        queue->tail = queue->tail->next;
    }
    queue->elem_size += 1;

    return true;
}

bool
queue_remove(Queue *queue, void *val_addr)
{
    assert(queue != NULL);
    QNode *qn;

    if (queue->head == NULL) return false;
    memcpy(val_addr, queue->head->val, queue->elem_size);
    qn = queue->head;
    queue->head = queue->head->next;
    queue->len -= 1;
    if (qn == queue->tail) queue->tail = queue->head;
    q_node_free(qn);

    return true;
}

bool
queue_is_empty(Queue *queue)
{
    assert(queue != NULL);
    return (queue->head == NULL);
}

int
queue_size(Queue *queue)
{
    assert(queue != NULL);
    return queue->len;
}

void
queue_free(Queue *queue)
{
    assert(queue != NULL);
    QNode *tmp, *qn = queue->head;

    while (qn != NULL) {
        tmp = qn;
        qn = qn->next;
        q_node_free(tmp);
    }
    free(queue);
    queue = NULL;
}

/** Queue Node functions. **/
QNode *
q_node_new(const void *val_addr, int elem_size)
{
    QNode *node;
    if ( (node = (QNode *)malloc(sizeof(QNode))) == NULL ) {
        return NULL;
    }
    if ( (node->val = malloc(elem_size)) == NULL ) {
        free(node);
        return NULL;
    }
    memcpy(node->val, val_addr, elem_size);
    node->next = NULL;
    return node;
}

void
q_node_free(QNode *qnode)
{
    assert(qnode != NULL);
    free(qnode->val);
    free(qnode);
    qnode = NULL;
}
