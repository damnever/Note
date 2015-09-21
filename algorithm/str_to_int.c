#include <stdio.h>
#include <limits.h>

int myAtoi(char *str);

int main()
{
    char str1[] = "  1234567";
    char str2[] = "54321abc";
    char str3[] = "2147483648";
    char str4[] = "-2147483647";
    printf("%d\n", myAtoi(str1));
    printf("%d\n", myAtoi(str2));
    printf("%d\n", myAtoi(str3));
    printf("%d\n", myAtoi(str4));

    return 0;
}

int myAtoi(char *str)
{
    long result = 0;
    int sign = 1;
    char *start = str;

    while(*start == ' ') {
        start++;
    }
    if(*start == '+' || *start == '-') {
        sign = *start == '+' ? 1 : 0;
        start++;
    }
    if(!(*start >= '0' && *start <= '9')) {
        return 0;
    }
    while((*start >= '0' && *start <= '9') && result < INT_MAX) {
        result = result * 10 + *start - '0' + 0;
        start++;
    }
    if(result > INT_MAX) {
        return sign == 1 ? INT_MAX : INT_MIN;
    }
    return sign == 1 ? result : -result;
}
