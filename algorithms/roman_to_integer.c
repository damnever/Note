#include <stdio.h>

int roman_to_int(char *s);
int get_int_by_roman(char c);


int main()
{
    printf("%d\n", roman_to_int("D"));  // 500
    printf("%d\n", roman_to_int("XL"));  // 40
    printf("%d\n", roman_to_int("XIV"));  // 14
    printf("%d\n", roman_to_int("MMMCCCXXXIII"));  // 3333
    printf("%d\n", roman_to_int("MCM"));  // 1900
    printf("%d\n", roman_to_int("MCDXXXVII"));  // 1437
    return 0;
}

int roman_to_int(char *s)
{
    int result = 0;
    int current, next;

    while(*s && *(s+1)){
        current = get_int_by_roman(*s);
        next = get_int_by_roman(*(s+1));
        result += (current < next ? -current : current);
        s++;
    }
    result += get_int_by_roman(*s);
    return result;
}

int get_int_by_roman(char s)
{
    int num = 0;
    switch (s) {
        case 'I':
        case 'i':
            num = 1;
            break;
        case 'V':
        case 'v':
            num = 5;
            break;
        case 'X':
        case 'x':
            num = 10;
            break;
        case 'L':
        case 'l':
            num = 50;
            break;
        case 'C':
        case 'c':
            num = 100;
            break;
        case 'D':
        case 'd':
            num = 500;
            break;
        case 'M':
        case 'm':
            num = 1000;
            break;
        default:
            break;
    }
    return num;
}
