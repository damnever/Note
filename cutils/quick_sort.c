/** A simple generic quick sort.
 *
 * Example usage:
 *   // memcmp(x, y, sizeof(int))
 *   int cmp(void *x, void *y)
 *   {
 *       int v_x = *((int *)x);
 *       int v_y = *((int *)y);
 *
 *       if (v_x < v_y) return -1;
 *       return 1;
 *   }
 *
 *   int main()
 *   {
 *       int i;
 *       const int len = 6;
 *       int elems[len] = {3, 5, 4, 2, 6, 1};
 *       for (i = 0; i < len; ++i) {
 *           printf("%d ", elems[i]);
 *       }
 *       printf("\n");
 *       quick_sort(elems, len, sizeof(int), cmp);
 *       for (i = 0; i < len; ++i) {
 *           printf("%d ", elems[i]);
 *       }
 *       printf("\n");
 *       return 0;
 *   }
**/
#include "quick_sort.h"

void q_recursive_sort(void *elems, int elem_size, int start, int end, int (*cmp)(void *, void *));
int q_partition(void *elems, int elem_size, int start, int end, int (*cmp)(void *, void *));

void
quick_sort(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *))
{
    q_recursive_sort(elems, elem_size, 0, elem_num-1, cmp);
}

void
q_recursive_sort(void *elems, int elem_size, int start, int end, int (*cmp)(void *, void *))
{
    if (start > end) return;

    int pos = q_partition(elems, elem_size, start, end, cmp);
    q_recursive_sort(elems, elem_size, start, pos-1, cmp);
    q_recursive_sort(elems, elem_size, pos+1, end, cmp);
}

int
q_partition(void *elems, int elem_size, int start, int end, int (*cmp)(void *, void *))
{
    char tmp[elem_size];
    void *left, *right, *pivot, *pos;
    int first;

    pivot = (char *)elems + start * elem_size;
    first = start;
    start += 1;

    while (start <= end) {
        while (start <= end) {
            left = (char *)elems + start * elem_size;
            if ( cmp(left, pivot) < 0 ) {
                start += 1;
            } else {
                break;
            }
        }
        while (start <= end) {
            right = (char *)elems + end * elem_size;
            if ( cmp(right, pivot) > 0 ) {
                end -= 1;
            } else {
                break;
            }
        }
        if (start <= end) {
            memcpy(tmp, left, elem_size);
            memcpy(left, right, elem_size);
            memcpy(right, tmp, elem_size);
        }
    }

    // exchange pivot and first;
    pos = (char *)elems + end * elem_size;
    memcpy(tmp, pivot, elem_size);
    memcpy(pivot, pos, elem_size);
    memcpy(pos, tmp, elem_size);
    return end;
}
