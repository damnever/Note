#include <stdio.h>
#include <stdbool.h>

/*
 * https://leetcode.com/problems/climbing-stairs/
 * f(1) = 1
 * f(2) = 2
 * f(n) = f(n-1) + f(n-2) first step 1 or 2, the rest...
 */

int climb_stairs(int n)
{
    int one = 1, two = 1;
    int i, tmp;

    for(i=1; i < n; i++){
        tmp = two;
        two = one + two;
        one = tmp;
    }

    return two;
}

int main()
{
    printf("<%d> stairs has <%d> ways\n", 6, climb_stairs(6));
    printf("<%d> stairs has <%d> ways\n", 1, climb_stairs(1));
    return 0;
}
