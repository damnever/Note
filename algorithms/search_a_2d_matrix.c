// https://leetcode.com/problems/search-a-2d-matrix/

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    int left = 0, right = matrixRowSize*matrixColSize - 1;
    for (;left <= right;) {
        int mid = (left + right) / 2;
        int v = matrix[mid/matrixColSize][mid%matrixColSize];
        if (v > target) {
            right = mid - 1;
        } else if (v < target) {
            left = mid + 1;
        } else {
            return true;
        }
    }
    return false;
}

int main(int argc, const char *argv[])
{
    int** matrix = (int**)malloc(sizeof(int*)*3);
    int row0[4] = {1,   3,  5,  7};
    matrix[0] = (int*)malloc(sizeof(int)*4);
    memcpy(matrix[0], row0, sizeof(row0));
    int row1[4] = {10, 11, 16, 20};
    matrix[1] = (int*)malloc(sizeof(int)*4);
    memcpy(matrix[1], row1, sizeof(row1));
    int row2[4] = {23, 30, 34, 50};
    matrix[2] = (int*)malloc(sizeof(int)*4);
    memcpy(matrix[2], row2, sizeof(row2));

    printf("%s\n", searchMatrix(matrix, 3, 4, 3) ? "true" : "false");
    printf("%s\n", searchMatrix(matrix, 3, 4, 13) ? "true" : "false");

    free(matrix[0]);
    free(matrix[1]);
    free(matrix[2]);
    free(matrix);
    return 0;
}
