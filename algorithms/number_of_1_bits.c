#include <stdio.h>
#include <stdint.h>

/*
 * https://leetcode.com/problems/number-of-1-bits/
 */

int
hammingWeight(uint32_t num)
{
    int i, count;
    uint32_t tmp;

    count = 0;
    for (i = 0; i < (int)(sizeof(uint32_t) * 8); i++) {
        tmp = num >> 1;
        if ((tmp << 1) + 1 == num) {
            count += 1;
        }
        num = tmp;
    }

    return count;
}

int
main()
{
    printf("%d\n", hammingWeight(10));
    printf("%d\n", hammingWeight(11));

    return 0;
}
