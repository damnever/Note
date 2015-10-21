#include <stdio.h>

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

void
swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void
shell_sort(int *nums, int len)
{
    int gap, i, j;

    for (gap = len / 2; gap > 0; gap /= 2) {
        for (i = gap; i < len; ++i) {
            for (j = i; j >= gap && nums[j] < nums[j -gap]; j -= gap) {
                swap(&nums[j], &nums[j - gap]);
            }
        }
    }
}

void
print_arr(int *nums, int len)
{
    while((len--) > 0) {
        printf("%d ", *nums++);
    }
    printf("\n");
}

int
main()
{
    int nums[] = {2, 4, 3, 1, 5, 9, 10, 8, 7, 6};
    int len = arr_len(nums);

    print_arr(nums, len);
    shell_sort(nums, len);
    print_arr(nums, len);

    return 0;
}
