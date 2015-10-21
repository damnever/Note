#include <stdio.h>
#include <stdbool.h>

void quick_sort(int *nums, int start, int end);
int partition(int *nums, int start, int end);
void print(int *nums, int len);

int main()
{
    int nums[10] = {10, 2, 9, 8, 7, 6, 1, 3, 5, 4};
    print(nums, 10);
    quick_sort(nums, 0, 9);
    print(nums, 10);

    return 0;
}

void quick_sort(int *nums, int start, int end)
{
    if(start > end) return;

    int pos = partition(nums, start, end);
    quick_sort(nums, start, pos-1);
    quick_sort(nums, pos+1, end);
}

int partition(int *nums, int start, int end)
{
    int tmp;
    int pivot = nums[start];
    int first = start;
    start += 1;

    while(true){
        while(start <= end && nums[start] <= pivot){
            start += 1;
        }
        while(start <= end && nums[end] > pivot){
            end -= 1;
        }
        if(start > end)
            break;
        else{
            tmp = nums[start];
            nums[start] = nums[end];
            nums[end] = tmp;
        }
    }
    tmp = nums[first];
    nums[first] = nums[end];
    nums[end] = tmp;
    return end;
}

void print(int *nums, int len)
{
    while((len--) > 0){
        printf("%d ", *nums++);
    }
    printf("\n");
}
