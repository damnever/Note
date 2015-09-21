#include <stdio.h>

// https://leetcode.com/problems/length-of-last-word/

int length_of_last_word(char *s);


int main()
{
    printf("%d\n", length_of_last_word(""));
    printf("%d\n", length_of_last_word("Hello World"));
    return 0;
}

int length_of_last_word(char *s)
{
    int length = 0;

    while(*s) s++;
    s--;
    while(*s && ' ' == *s) s--;

    while(*s && ' ' != *s){
        s--;
        length++;
    }

    return length;
}
