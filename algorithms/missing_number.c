#include <stdio.h>

/*
 * https://leetcode.com/problems/missing-number/
 */

int
missingNumber(int *nums, int numsSize)
{
    int expected;

    expected = (numsSize + 1) * numsSize / 2;
    for (numsSize -= 1; numsSize >= 0; numsSize--) {
        expected -= nums[numsSize];
    }

    return expected;
}

int
main()
{
    int nums[] = {0, 1, 3};
    int len = (sizeof(nums) / sizeof(*nums));
    printf("%d\n", missingNumber(nums, len));

    return 0;
}
