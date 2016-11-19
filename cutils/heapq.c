/* A generic heap queue
 *
 * Example:
 *
 *   #include <stdio.h>
 *   #define len 6
 *
 *   // memcmp(x, y, sizeof int), max heap
 *   int cmp(void *x, void *y)
 *   {
 *       int v_x = *((int*)x);
 *       int v_y = *((int*)y);
 *       if (v_x > v_y) return -1;
 *       return 1;
 *   }
 *
 *   void print(int *elems, int size)
 *   {
 *       for (; size > 0; --size) {
 *           int val;
 *           heap_pop(elems, &val, size, sizeof(int), cmp);
 *           printf("%d ", val);
 *       }
 *       printf("\n");
 *   }
 *
 *   int main()
 *   {
 *       int elems[len] = {3, 5, 1, 7, 9};
 *       int elem = 11;
 *       heapify(elems, len-1, sizeof(int), cmp);
 *       heap_push(elems, &elem, len-1, sizeof(int), cmp);
 *       print(elems, len);
 *
 *       for (int i = 0; i < len; ++i) {
 *           heap_push(elems, &i, i, sizeof(int), cmp);
 *       }
 *       int val = 6;
 *       heap_push_pop(elems, &val, len, sizeof(int), cmp);
 *       printf("%d\n", val);
 *       print(elems, len);
 *
 *       return 0;
 *   }
 */
#include <string.h>
#include "heapq.h"

#define idx_parent(idx) ( ((idx) - 1) >> 1 )
#define idx_lchild(idx) ( ((idx) << 1) + 1 )
#define idx_rchild(idx) ( ((idx) << 1) + 2 )

static void _sift_up(void *elems, int pos, int elem_num,
                     int elem_size, int (*cmp)(void *, void *));
static void _sift_down(void *elems, int start, int end,
                       int elem_size, int (*cmp)(void *, void *));



/* make a heap, max or min according to the cmp function. */
void
heapify(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *))
{
    for (int end = idx_parent(elem_num-1); end >= 0; --end) {
        _sift_up(elems, end, elem_num, elem_size, cmp);
    }
}

/* push the :elem: to heap.
 * must make sure memory block :elem_num: * :elem_size: can be access.
 */
void
heap_push(void *elems, void *elem, int elem_num,
          int elem_size, int (*cmp)(void *, void *))
{
    char *en = (char*)elems + elem_num * elem_size;
    memcpy(en, elem, elem_size);
    if (elem_num > 0) {
        _sift_down(elems, 0, elem_num, elem_size, cmp);
    }
}

/* pop the top heap element, and copy the data to :elem:. */
void
heap_pop(void *elems, void *elem, int elem_num,
         int elem_size, int (*cmp)(void *, void *))
{
    if (elem_num == 0) {
        return;
    }
    char *es = (char*)elems;
    char *ee = (char*)elems + (elem_num-1)*elem_size;

    memcpy(elem, es, elem_size);
    memcpy(es, ee, elem_size);
    _sift_up(elems, 0, elem_num-1, elem_size, cmp);
}

/* push the :elem: to heap, then return the heap element as :elem: */
void heap_push_pop(void *elems, void *elem, int elem_num,
                   int elem_size, int (*cmp)(void *, void *))
{
    if (elem_num == 0) {
        return;
    }

    char tmp[elem_size];
    char *es = (char*)elems;
    if (cmp(elem, es) <= 0) return;

    memcpy(tmp, es, elem_size);
    memcpy(elem, tmp, elem_size);
    memcpy(es, elem, elem_size);
    _sift_up(elems, 0, elem_num, elem_size, cmp);
}


/* move the smallest up */
static void
_sift_up(void *elems, int pos, int elem_num,
         int elem_size, int (*cmp)(void *, void *))
{
    int start = pos;
    char *tmp[elem_size];
    char *en = (char*)elems + pos * elem_size;
    memcpy(tmp, en, elem_size);

    for (int ch_idx = idx_lchild(pos);
            ch_idx < elem_num;
            pos = ch_idx, ch_idx = idx_lchild(pos)) {
        char *smallest = (char*)elems + ch_idx*elem_size;
        int rch_idx = ch_idx + 1;

        if (rch_idx < elem_num) {
            char *erc = smallest + elem_size;
            if (cmp(erc, smallest) < 0) {
                smallest = erc;
                ch_idx = rch_idx;
            }
        }
        memcpy(en, smallest, elem_size);
        en = smallest;
    }

    memcpy(en, tmp, elem_size);
    // repair the heap
    _sift_down(elems, start, pos, elem_size, cmp);
}

/* move the larger down */
static void
_sift_down(void *elems, int start, int end,
           int elem_size, int (*cmp)(void *, void *))
{
    char tmp[elem_size];
    char *en = (char*)elems + end * elem_size;
    memcpy(tmp, en, elem_size);

    while (end > start) {
        int par_idx = idx_parent(end);
        char *ep = (char*)elems + par_idx * elem_size;
        if (cmp(ep, tmp) <= 0) break;
        memcpy(en, ep, elem_size);
        end = par_idx;
        en = ep;
    }
    memcpy(en, tmp, elem_size);
}
