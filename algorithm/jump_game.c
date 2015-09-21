#include <stdio.h>
#include <stdbool.h>

/*
 * https://leetcode.com/problems/jump-game/
 * Use __typeof__
 */
#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))
#define max(a, b) ({__typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        (void) (&_a == &_b); \
        _a > _b ? _a : _b; })

bool
canJump(int *nums, int numsSize)
{
    int idx, step;
    if(numsSize <= 0) return false;

    idx = 0;
    step = nums[idx++];
    while(idx < numsSize) {
        if(step > 0) {
            step = max(nums[idx++], --step);
        } else {
            return false;
        }
    }
    return true;
}

int
main()
{
    int nums1[] = {2, 3, 1, 1, 4};
    int nums2[] = {3, 2, 1, 0, 4};
    int nums3[] = {1};
    int nums4[] = {2, 5, 0, 0};
    printf("%d\n", canJump(nums1, arr_len(nums1)));
    printf("%d\n", canJump(nums2, arr_len(nums2)));
    printf("%d\n", canJump(nums3, arr_len(nums3)));
    printf("%d\n", canJump(nums4, arr_len(nums4)));

    return 0;
}
