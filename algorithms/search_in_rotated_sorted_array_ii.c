// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
// FIXME(damnever): we can improve it on some cases, but..

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool search(int *nums, int numsSize, int target) {
    int l = 0, r = numsSize - 1;

    for (; l <= r;) {
        int mid = (l + r) / 2;
        int v = nums[mid];
        if (v == target) {
            return true;
        }

        int lv = nums[l], rv = nums[r];
        if (v > target) {
            bool left = true;
            if (lv > rv && target <= rv && v > rv) {
                left = false;
            } else if (lv == v || v == rv || lv == rv) {
                if (search(nums + l, mid - l, target)) {
                    return true;
                }
                return search(nums + mid + 1, r - mid, target);
            }

            if (left) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {  // v < target
            bool right = true;
            if (lv > rv && target >= lv && v < rv) {
                right = false;
            } else if (lv == v || v == rv || lv == rv) {
                if (search(nums + l, mid - l, target)) {
                    return true;
                }
                return search(nums + mid + 1, r - mid, target);
            }

            if (right) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return false;
}

int main(int argc, const char *argv[]) {
    {
        int nums[] = {4, 5, 6, 7, 0, 1, 2};
        printf("%s\n", search(nums, 7, 0) ? "true" : "false");
        printf("%s\n", search(nums, 7, 3) ? "true" : "false");
    }
    {
        int nums[] = {1, 1, 3, 1};
        printf("%s\n", search(nums, 4, 3) ? "true" : "false");
    }
    {
        int nums[] = {1, 3, 1, 1, 1};
        printf("%s\n", search(nums, 5, 3) ? "true" : "false");
    }
    {
        int nums[] = {3, 1};
        printf("%s\n", search(nums, 2, 1) ? "true" : "false");
    }
    {
        int nums[] = {1, 2, 2, 2, 0, 1, 1};
        printf("%s\n", search(nums, 7, 0) ? "true" : "false");
    }
    {
        int nums[] = {1, 2, 1};
        printf("%s\n", search(nums, 3, 1) ? "true" : "false");
    }
    {
        int nums[] = {3, 1, 2, 2, 2};
        printf("%s\n", search(nums, 5, 1) ? "true" : "false");
    }
    {
        int nums[] = {3, 1, 1};
        printf("%s\n", search(nums, 3, 3) ? "true" : "false");
    }
    return 0;
}
