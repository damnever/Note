#include <stdio.h>

/*
 * https://leetcode.com/problems/merge-sorted-array/
 */

void merge(int *nums1, int m, int *nums2, int n)
{
    int len = m + n;

    m--; n--;
    while(m >= 0 && n >= 0){
        if(nums1[m] > nums2[n]){
            nums1[--len] = nums1[m--];
        }else{
            nums1[--len] = nums2[n--];
        }
    }
    while(n >= 0){  // nums2 does not finished
        nums1[--len] = nums2[n--];
    }
}

void print_arr(int *nums, int len){
    while((len--) > 0){
        printf("%d ", *nums++);
    }
    printf("\n");
}

int main()
{
    int nums1[] = {1, 3, 5, 7, 0, 0};
    int nums2[] = {2, 4};
    print_arr(nums1, 4);
    print_arr(nums2, 2);
    merge(nums1, 4, nums2, 2);
    print_arr(nums1, 6);

    return 0;
}
