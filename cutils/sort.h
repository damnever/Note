#ifndef _SORT_H_
#define _SORT_H_

#include <string.h>

void quick_sort(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *));

#endif
