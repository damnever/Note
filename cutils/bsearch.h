#ifndef _BSEARCH_H_
#define _BSEARCH_H_

#include <stdbool.h>

bool binary_search(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *), void *val, int *idx);

#endif
