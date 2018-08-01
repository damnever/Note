// https://leetcode.com/problems/factorial-trailing-zeroes/description/
#include <stdio.h>

int trailingZeroes(int n)
{
    // I'm using inductive and deductive reasoning..
    // 5(1) 10(2) 15(3) 20(4) 25(6) 30(7) 50(12) ...
    int zeroes = 0;
    for (n = n / 5; n > 0; n = n / 5) {
        zeroes += n;
    }
    return zeroes;
}

int main()
{
    printf("%d\n", trailingZeroes(3));
    printf("%d\n", trailingZeroes(5));
    printf("%d\n", trailingZeroes(25));
    printf("%d\n", trailingZeroes(50));
    return 0;
}
