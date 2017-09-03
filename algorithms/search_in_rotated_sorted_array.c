// https://leetcode.com/problems/search-in-rotated-sorted-array/description/

#include <stdio.h>

int search(int* nums, int size, int target)
{
    if (size == 0) return -1;

    int l = 0, r = size-1;

    for (;l <= r;) {
        int first = nums[l], last = nums[r];
        int mid = (l+r) / 2;
        int v = nums[mid];
        if (v == target) return mid;
        if (target < v) {
            if (first > last && target <= last && v > last) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        } else {
            if (first > last && first > v && target > last) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }

    return -1;
}

int main()
{
    int nums1[] = {0, 1, 2, 3, 4, 5, 6, 7};
    printf("%d\n", search(nums1, 8, 5));

    int nums2[] = {4, 5, 6, 7, 0, 1, 2, 3};
    printf("%d\n", search(nums2, 8, 6));
    printf("%d\n", search(nums2, 8, 0));
    printf("%d\n", search(nums2, 8, 2));

    int nums3[] = {4, 5, 6, 7, 8, 1, 2, 3};
    printf("%d\n", search(nums3, 8, 8));

    int nums4[] = {7, 8, 1, 2, 3, 4, 5, 6};
    printf("%d\n", search(nums4, 8, 1));
    printf("%d\n", search(nums4, 8, 4));
    return 0;
}
