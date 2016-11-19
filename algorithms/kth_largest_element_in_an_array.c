#include <stdio.h>
#include <assert.h>
#include "../cutils/heapq.h"


/*
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 */

int cmp(void *x, void *y)
{
    int vx = *((int*)x);
    int vy = *((int*)y);

    if (vx > vy) return -1;
    return 1;
}

int findKthLargest(int* nums, int numsSize, int k)
{
    int esize = sizeof(int);
    heapify(nums, numsSize, esize, cmp);

    int val;
    for (; k > 0; --k, --numsSize) {
        heap_pop(nums, &val, numsSize, esize, cmp);
    }

    return val;
}


int main()
{
    int nums1[] = {2, 21, 12, 3, 6, 9};
    assert(12 == findKthLargest(nums1, 6, 2));
    int nums2[] = {3, 1, 2, 4};
    assert(3 == findKthLargest(nums2, 4, 2));

    return 0;
}
