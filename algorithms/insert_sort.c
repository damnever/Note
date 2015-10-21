#include <stdio.h>

void insert_sort(int *nums, int len)
{
    int i, j, tmp;

    for(i=1; i < len; i++){
        j = i - 1;
        if(nums[i] < nums[j]) {
            tmp = nums[i];
            for(; j >= 0 && nums[j] > tmp; j--){
                nums[j+1] = nums[j];
            }
            nums[j+1] = tmp;
        }
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
    int nums[7] = {1, 6, 8, 2, 10, 4, 9};
    print(nums, 7);
    insert_sort(nums, 7);
    print(nums, 7);

    return 0;
}
