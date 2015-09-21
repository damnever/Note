#include <stdio.h>


void selection_sort(int *nums, int len)
{
    int i, max_idx, tmp;

    len -= 1;
    while(len > 0){
        max_idx = 0;
        for(i=1; i <= len; i++){
            if(nums[i] > nums[max_idx]){
                max_idx = i;
            }
        }
        tmp = nums[len];
        nums[len] = nums[max_idx];
        nums[max_idx] = tmp;
        len -= 1;
    }
}

void print(int *nums, int len)
{
    while((len--) > 0){
        printf("%d ", *nums++);
    }
    printf("\n");
}

int main()
{
    int nums[7] = {1, 5, 3, 9, 6, 8, 10};
    print(nums, 7);
    selection_sort(nums, 7);
    print(nums, 7);

    return 0;
}
