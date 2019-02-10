// https://leetcode.com/problems/peak-index-in-a-mountain-array/

#include<stdio.h>

int peakIndexInMountainArray(int* A, int ASize) {
    int left = 0, right = ASize-1;

    for (;left <= right;) {
        int mid = (left+right)/2;
        if (A[mid-1] > A[mid]) {
            right = mid-1;
        } else if (A[mid+1] > A[mid]) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return -1; // Unreachable.
}

int main(int argc, const char *argv[])
{
    int a[] = {0, 2, 1, 0};
    printf("%d\n", peakIndexInMountainArray(a, 4));
    return 0;
}
