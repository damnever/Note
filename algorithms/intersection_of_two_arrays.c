/*
 * https://leetcode.com/problems/intersection-of-two-arrays/
 *
 * Python: so easy!
 * Golang: easy!
 * C: binary search tree? hash table? fucking wheels...
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int
partition(int *nums, int start, int end)
{
    int tmp, first = start, pivot = nums[first];

    start += 1;
    for (;;) {
        for (; start <= end && nums[start] <= pivot; ++start);
        for (; start <= end && nums[end] > pivot; --end);
        if (start > end) {
            break;
        } else {
            tmp = nums[start];
            nums[start] = nums[end];
            nums[end] = tmp;
        }
    }

    tmp = nums[first];
    nums[first] = nums[end];
    nums[end] = tmp;
    return end;
}

void
quick_sort(int *nums, int start, int end)
{
    int pos;
    if (start > end) return;

    pos = partition(nums, start, end);
    quick_sort(nums, start, pos-1);
    quick_sort(nums, pos+1, end);
}

bool
search(int *nums, int size, int val)
{
    int start, end, mid, cmp;

    for (start = 0, end = size - 1; start <= end;) {
        mid = (start + end) / 2;
        if ( (cmp = nums[mid] - val) == 0) {
            return true;
        } else if (cmp < 0) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return false;
}

int *
intersection(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{
    int minSize, maxSize, idx, num;
    int *minNums, *maxNums, *nums;

    quick_sort(nums1, 0, nums1Size-1);
    quick_sort(nums2, 0, nums2Size-1);
    minSize = nums1Size;
    minNums = nums1;
    maxSize = nums2Size;
    maxNums = nums2;
    if (nums1Size > nums2Size) {
        minSize = nums2Size;
        minNums = nums2;
        maxSize = nums1Size;
        maxNums = nums1;
    }

    nums = (int *)malloc(sizeof(int) * minSize);
    memset(nums, 0, sizeof(int) * minSize);
    *returnSize = 0;

    for (idx = 0; idx < minSize; ++idx) {
        num = minNums[idx];
        if (search(maxNums, maxSize, num) && !search(nums, *returnSize, num)) {
            nums[(*returnSize)++] = num;
        }
    }

    return nums;
}

int
main()
{
    int nums1[] = {1, 3, 2, 2};
    int nums2[] = {2, 3};
    int *nums = NULL;
    int size = 0;

    nums = intersection(nums1, 4, nums2, 2, &size);

    for (; size > 0; --size) {
        printf("%d ", nums[size-1]);
    }
    printf("\n");
    free(nums);

    return 0;
}
