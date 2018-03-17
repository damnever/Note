/*
 * https://leetcode.com/problems/sort-colors/description/
*/
#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortColors(int* nums, int numsSize) {
    int tmp, r = 0, b = numsSize-1;

    for (int i = 0; i <= b;) {
        tmp = nums[i];
        if (tmp == 2) {
            swap(nums+i, nums+b);
            b--;
            continue;
        }
        if (tmp == 0) {
            swap(nums+i, nums+r);
            r++;
        }
        i++;
    }
}

int main() {
    int nums[6] = {0, 1, 2, 0, 1, 2};
    sortColors(nums, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}
