// https://leetcode.com/problems/sqrtx/

#include<stdio.h>

int mySqrt(int x) {
    int left = 0, right = x;
    long long target = (long long) x;
    for (;left <= right;) {
        int mid = (left + right) / 2;
        long long lmid = (long long) mid;
        long long v = lmid * lmid; // Avoid overflow..
        if (v > target) {
            right = mid - 1;
        } else if (v < target) {
            if ((lmid+1)*(lmid+1) > target) {
                return mid;
            }
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return -1; // Unreachable!
}

int main(int argc, const char *argv[])
{
    printf("%d\n", mySqrt(4));
    printf("%d\n", mySqrt(8));
    printf("%d\n", mySqrt(2147395599));
    return 0;
}
