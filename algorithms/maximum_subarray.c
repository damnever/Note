// https://leetcode.com/problems/maximum-subarray/description/

#include <stdio.h>
#include <stdlib.h>


int maxSubArray(int* nums, int numsSize)
{
    if (numsSize == 0) { return 0; }
    if (numsSize == 1) { return nums[0]; }
    int max = nums[0], x;

    for (int i = 1; i < numsSize; i++) {
        if ((x = nums[i-1]) > 0) {
            x = nums[i] + x;
            nums[i] = x;
        } else {
            x = nums[i];
        }
        if (x > max) {
            max = x;
        }
    }

    return max;
}


int main(void)
{
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printf("%d\n", maxSubArray(nums, 9));
    return 0;
}
