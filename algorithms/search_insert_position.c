#include <stdio.h>

/*
 * https://leetcode.com/problems/search-insert-position/
 */

int searchInsert(int *nums, int numsSize, int target)
{
    int start, end, mid;

    start = 0;
    end = numsSize - 1;
    for (;start < end;) {
        mid = (start + end) / 2;
        if (nums[mid] < target) {
            start = mid + 1;
        } else if (nums[mid] > target) {
            end = mid - 1;
        } else {
            return mid;
        }
    }
    if (target > nums[end]) {
        return (end + 1);
    }
    return start;
}


int main()
{
    int nums[] = {1, 3, 5, 6};
    int len = sizeof(nums) / sizeof(*nums);

    printf("%d\n", searchInsert(nums, len, 5));
    printf("%d\n", searchInsert(nums, len, 2));
    printf("%d\n", searchInsert(nums, len, 7));
    printf("%d\n", searchInsert(nums, len, 0));

    return 0;
}
