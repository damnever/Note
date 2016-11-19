#ifndef _HEAPQ_H_
#define _HEAPQ_H_

void heapify(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *));
void heap_push(void *elems, void *elem, int elem_num,
               int elem_size, int (*cmp)(void *, void *));
void heap_pop(void *elems, void *elem, int elem_num,
              int elem_size, int (*cmp)(void *, void *));
void heap_push_pop(void *elems, void *elem, int elem_num,
                   int elem_size, int (*cmp)(void *, void *));

#endif
