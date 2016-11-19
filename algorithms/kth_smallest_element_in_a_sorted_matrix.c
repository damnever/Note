#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../cutils/heapq.h"

/*
 * https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
 *
 * fucking dynamaic array, may trying some other ways...
 */

int cmp(void *x, void *y)
{
    int vx = *((int*)x);
    int vy = *((int*)y);

    if (vx > vy) return 1;
    return -1;
}

int kthSmallest(int **matrix, int matrixRowSize, int matrixColSize, int k) {
    int nums[matrixRowSize*matrixColSize], c = 0, esize = sizeof(int);

    for (int i = 0; i < matrixRowSize; ++i) {
        for (int j = 0; j < matrixColSize; ++j) {
            heap_push(nums, &(matrix[i][j]), c, esize, cmp);
            c += 1;
        }
    }

    int val;
    for (; k > 0; --k, --c) {
        heap_pop(nums, &val, c, esize, cmp);
    }

    return val;
}


int main()
{
    int nums[][3] = {
        {1,  5,  9},
        {10, 11, 13},
        {12, 13, 15},
    };
    int **matrix = (int **)calloc(sizeof(int*), 3);
    for (int i = 0; i < 3; ++i) {
        matrix[i] = (int*)calloc(sizeof(int), 3);
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = nums[i][j];
        }
    }
    printf("%d\n", kthSmallest(matrix, 3, 3, 8));

    return 0;
}
