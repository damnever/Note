#include <stdio.h>

/*
 * https://leetcode.com/problems/single-number/
 */

int
singleNumber(int *nums, int numsSize)
{
    int i, result;

    result = 0;
    for (i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }

    return result;
}


int
main()
{
    int nums[] = {1, 4, 3, 2, 1, 5, 2, 5, 4};
    int len = sizeof(nums) / sizeof(*nums);
    printf("%d\n", singleNumber(nums, len));

    return 0;
}
