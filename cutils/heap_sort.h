#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

void heap_sort(void *elems, int elem_num,
               int elem_size, int (*cmp)(void *, void *));
void heap_push(void *elems, int elem_num, void *elem,
               int elem_size, int (*cmp)(void *, void *));
void heap_pop(void *elems, int elem_num, void *elem,
              int elem_size, int (*cmp)(void *, void *));

#endif
