// https://leetcode.com/problems/sum-of-two-integers/description/

#include <stdio.h>

int sum(int x, int y)
{
    if (x == 0) return y;
    for (;y!=0;) {
        int carray = x & y;
        x = x ^ y;
        y = carray << 1;
    }
    return x;
}

int main()
{
    printf("sum(1, 2) = %d\n", sum(1, 22));
    return 0;
}
