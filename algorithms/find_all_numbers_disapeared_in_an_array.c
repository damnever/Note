// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/description/

#include <stdio.h>
#include <stdlib.h>

#define arr_len(arr) ()

int *findDisappearedNumbers(int *nums, int n, int *nr)
{
    for (int i = 0; i < n; i++) {
        int v = nums[i];
        v = v > 0 ? v : -v;
        int v2 = nums[v-1];
        if (v2 > 0) {
            nums[v-1] = -v2;
        }
    }

    int *arr = (int *)calloc(n, sizeof(int));
    *nr = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            arr[(*nr)++] = i+1;
        }
    }
    return arr;
}

int main()
{
    int nums[] = {3, 11, 8, 16, 4, 15, 4, 17, 14, 14, 6, 6, 2, 8, 3, 12, 15, 20, 20, 5};
    int n = (int)(sizeof(nums) / sizeof(*nums));
    int nr;
    int *arr = findDisappearedNumbers(nums, n, &nr);
    for (int i = 0; i < nr; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
