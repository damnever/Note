#include <stdio.h>

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

void bubble_sort(int *nums, int len)
{
    int i, tmp;

    len -= 1;
    while(len > 0) {
        for(i=0; i < len; i++) {
            if(nums[i] > nums[i+1]){
                tmp = nums[i];
                nums[i] = nums[i+1];
                nums[i+1] = tmp;
            }
        }
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
    int nums[] = {2, 8, 6, 4, 10, 9};
    int len = arr_len(nums);
    print(nums, len);
    bubble_sort(nums, len);
    print(nums, len);

    return 0;
}
