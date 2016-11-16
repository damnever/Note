#include <stdio.h>
#include <stdlib.h>

/*
 * https://leetcode.com/problems/rotate-image/
 */


void rotate(int **matrix, int matrixRowSize, int matrixColSize)
{
    int begin, end, len;
    begin = 0;
    end = matrixRowSize - 1;
    len = end;

    for (int i = 0; i < matrixColSize / 2; i++) {
        for (int j = begin; j < end; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[len-j][i];
            matrix[len-j][i] = matrix[len-i][len-j];
            matrix[len-i][len-j] = matrix[j][len-i];
            matrix[j][len-i] = tmp;
        }
        begin += 1;
        end -= 1;
    }
}


void init(int ***matrix, int size)
{
    int n = 0;
    *matrix = (int **)calloc(sizeof(int *), size);

    for (int i = 0; i < size; i++) {
        (*matrix)[i] = (int *)calloc(sizeof(int), size);
        for (int j = 0; j < size; j++) {
            (*matrix)[i][j] = n;
            n += 1;
        }
    }
}

void destory(int ***matrix, int size)
{
    for (int i = 0; i < size; i++) {
        free((*matrix)[i]);
    }
    free((*matrix));
}


void print(int **matrix, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void example(int size)
{
    int **matrix;

    init(&matrix, size);
    print(matrix, size);

    rotate(matrix, size, size);
    print(matrix, size);

    destory(&matrix, size);
}


int main()
{
    for (int i = 1; i < 6; i++) {
        example(i);
        printf("---\n\n");
    }

    return 0;
}
