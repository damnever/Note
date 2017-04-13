// https://leetcode.com/problems/hamming-distance/
// use xor and hamming weight
#include <stdio.h>

int hammingDistance(int x, int y)
{
    int z = x ^ y;
    z = (z & 0x55555555) + ((z >> 1) & 0x55555555);
    z = (z & 0x33333333) + ((z >> 2) & 0x33333333);
    z = (z & 0x0f0f0f0f) + ((z >> 4) & 0x0f0f0f0f);
    z = (z & 0x00ff00ff) + ((z >> 8) & 0x00ff00ff);
    z = (z & 0x0000ffff) + ((z >> 16) & 0x0000ffff);
    return z;
}

int main()
{
    printf("%d\n", hammingDistance(1, 4));
    printf("%d\n", hammingDistance(93, 73));
    return 0;
}
