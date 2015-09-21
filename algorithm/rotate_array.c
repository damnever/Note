#include <stdio.h>

void rotate(int *nums, int numsSize, int k);

int main()
{
    int *bp;
    int nums[7] = {1, 2, 3, 4, 5, 6, 7};
    rotate(nums, 7 , 3);

    bp = nums;
    while(*bp) {
        printf("%d ", *bp);
        bp++;
    }
    return 0;
}

void rotate(int *nums, int numsSize, int k)
{
    if (0 == numsSize || 0 == k) return;
    int i, j, tmp;
    int start_pos = numsSize - k;

    for(i=0; i < k; i++) {
        for(j=start_pos+i; j > 0; j--) {
            tmp = nums[j];
            nums[j] = nums[j-1];
            nums[j-1] = tmp;
        }
    }
}
