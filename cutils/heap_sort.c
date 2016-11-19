/*
 * A generic heap sort.
 *
 * Example:
 *
 *   #include <stdio.h>
 *   #define len  5
 *
 *   // memcmp(x, y, sizeof int)
 *   int cmp(void *x, void *y)
 *   {
 *       int v_x = *((int *)x);
 *       int v_y = *((int *)y);
 *
 *       if (v_x < v_y) return -1;
 *       return 1;
 *   }
 *
 *   void print(int *elems, int size)
 *   {
 *       for (int i = 0; i < len; i++) {
 *           printf("%d ", elems[i]);
 *       }
 *       printf("\n");
 *   }
 *
 *   int main()
 *   {
 *       int elems[len] = {3, 5, 4, 2, 6};
 *       print(elems, len);
 *
 *       heap_sort(elems, len, sizeof(int), cmp);
 *       print(elems, len);
 *
 *       return 0;
 *   }
 */

#include <string.h>
#include "heap_sort.h"

#define idx_parent(idx) ( ((idx) - 1) >> 1 )
#define idx_lchild(idx) ( ((idx) << 1) + 1 )
#define idx_rchild(idx) ( ((idx) << 1) + 2 )

static void _sift_down(void *elems, int start, int end,
                        int elem_size, int (*cmp)(void *, void *));
static void _swap(void *x, void *y, int size);


void
heap_sort(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *))
{
    int end = elem_num - 1;
    for (int start = idx_parent(end); start >= 0; --start) {
        _sift_down(elems, start, end, elem_size, cmp);
    }

    while (end > 0) {
        char *ee = (char*)elems + end * elem_size;
        char *es = (char*)elems;
        _swap(ee, es, elem_size);
        end -= 1;
        _sift_down(elems, 0, end, elem_size, cmp);
    }
}

static void _sift_down(void *elems, int start, int end,
                        int elem_size, int (*cmp)(void *, void *))
{
    int lar_idx = start;
    int lch_idx = idx_lchild(start);

    while (lch_idx <= end) {
        char *largest;
        int par_idx = lar_idx;
        int rch_idx = lch_idx + 1;
        char *ep = (char *)elems + start * elem_size;
        char *elc = (char *)elems + lch_idx * elem_size;

        if (cmp(ep, elc) < 0) {
            lar_idx = lch_idx;
            largest = elc;
        }
        if (rch_idx <= end) {
            char *erc = elc + elem_size;
            if (cmp(ep, erc) < 0) {
                lar_idx = rch_idx;
                largest = erc;
            }
        }

        if (lar_idx == par_idx) break;
        _swap(ep, largest, elem_size);
        par_idx = lar_idx;
        lch_idx = idx_parent(par_idx);
    }

}

static void
_swap(void *x, void *y, int size)
{
    char tmp[size];
    memcpy(tmp, x, size);
    memcpy(x, y, size);
    memcpy(y, tmp, size);
}
