/** A simple generic binary search.
 *
 * Example usage:
 *   // memcmp(x, y, sizeof(int))
 *   int cmp(void *x, void *y)
 *   {
 *       int v_x = *((int *)x);
 *       int v_y = *((int *)y);
 *
 *       return (v_x - v_y);
 *   }
 *
 *   int main()
 *   {
 *       bool found;
 *       int idx;
 *       int nums[6] = {1, 3, 4, 5, 7, 9};
 *       int need = 7;
 *
 *       found = binary_search(nums, 6, sizeof(int), cmp, &need, &idx);
 *       printf("%s: %d\n", found ? "Y" : "N", idx);
 *       need = 2;
 *       found = binary_search(nums, 6, sizeof(int), cmp, &need, &idx);
 *       printf("%s: %d\n", found ? "Y" : "N", idx);
 *
 *       return 0;
 *   }
**/
#include "bsearch.h"

bool
binary_search(void *elems, int elem_num, int elem_size, int (*cmp)(void *, void *), void *val, int *idx)
{
    int start, end, mid, rcmp;
    void *mid_addr;

    for (start = 0, end = elem_num - 1; start <= end;) {
        mid = (start + end) / 2;
        mid_addr = (char *)elems + mid * elem_size;
        if ( (rcmp = cmp(mid_addr, val)) == 0 ) {
            *idx = mid;
            return true;
        } else if (rcmp < 0) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    *idx = start;
    return false;
}
