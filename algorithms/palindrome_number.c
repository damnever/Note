// https://leetcode.com/problems/palindrome-number/

#include <stdio.h>
#include <stdbool.h>

bool is_palindrom(int n)
{
    if (n >= 0 && n < 10) return true;
    if (n < 0 || n % 10 == 0) return false;
    int x = 0;
    for (;n > x;) {
        x = x * 10 + n % 10;
        n /= 10;
    }
    return (x == n) || (x/10 == n);
}

int main()
{
    printf("1? %s\n", (is_palindrom(1) ? "true" : "false"));
    printf("12? %s\n", (is_palindrom(12) ? "true" : "false"));
    printf("1221? %s\n", (is_palindrom(1221) ? "true" : "false"));
    printf("12321? %s\n", (is_palindrom(12321) ? "true" : "false"));
    return 0;
}
