#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include <string.h>

void quick_sort(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *));

#endif
