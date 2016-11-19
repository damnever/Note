#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

void heap_sort(void *elems, int elem_num,
               int elem_size, int (*cmp)(void *, void *));

#endif
