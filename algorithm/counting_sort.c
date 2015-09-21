#include <stdio.h>
#include <stdlib.h>

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

void counting_sort(int *nums, int len);
int max_num(int *nums, int len);
void print(int *nums, int len);

int main()
{
    int nums[] = {6, 4, 7, 8, 5, 6, 3, 9, 2, 1};
    int len = arr_len(nums);
    print(nums, len);
    counting_sort(nums, len);
    print(nums, len);

    return 0;
}

void counting_sort(int *nums, int len)
{
    int i, tmp, max = max_num(nums, len);
    int *cnums = (int *)malloc(max * sizeof(int));
    int *bp = nums;

    for(i=0; i < max; i++){
        cnums[i] = 0;
    }

    while((len--) > 0){
        cnums[*bp - 1] += 1;
        bp++;
    }
    print(cnums, max);

    bp = nums;
    for(i=0; i < max; i++){
        tmp = cnums[i];
        while((tmp--) > 0){
            *bp++ = i + 1;
        }
    }

    free(cnums);
    cnums = NULL;
}

int max_num(int *nums, int len)
{
    int max = 0;
    while((len--) > 0){
        if(*nums > max){
            max = *nums;
        }
        nums++;
    }
    return max;
}

void print(int *nums, int len)
{
    while((len--) > 0){
        printf("%d ", *nums++);
    }
    printf("\n");
}
