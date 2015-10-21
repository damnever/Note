#include <stdio.h>

/*
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 * IN-PLACE, return length.
 */

int removeDuplicates(int *nums, int numsSize)
{
    int i = 0, j, len = 0;
    while(i < numsSize){
        j = i;
        while(j + 1 < numsSize && nums[j] == nums[j+1]){
            j++;
        }
        if(j != i){  // duplicate, skip
            i = j;
        }else{
            nums[len++] = nums[i++];
        }
    }
    return len;
}

void print_arr(int *nums, int numsSize)
{
    int i;
    for(i=0; i < numsSize; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main()
{
    int len = 0;
    int arr[] = {1, 1, 2, 3, 4, 4, 5};
    print_arr(arr, 2);
    len = removeDuplicates(arr, 2);
    print_arr(arr, len);

    print_arr(arr, 7);
    len = removeDuplicates(arr, 7);
    print_arr(arr, len);

    return 0;
}
