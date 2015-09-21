#include <stdio.h>
#include <string.h>

// typedef enum {false, true} bool;

void reverseWords(char *s);
void reverseString(char *s, int start, int end);
void trim(char *s);

int main()
{
    char s1[] = " AB ";
    reverseWords(s1);
    char s2[] = "the sky is blue";
    reverseWords(s2);
    char s3[] = "a";
    reverseWords(s3);

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);

    return 0;
}


void reverseWords(char *s)
{
    if(s == NULL) return;
    if(strlen(s) <= 0) return;

    char *sub_str_start, *current_pos;

    trim(s);
    reverseString(s, 0, strlen(s)-1);

    current_pos = s;
    while(*current_pos != '\0') {
        sub_str_start = current_pos;
        while(*current_pos != ' ' && *current_pos != '\0'){
            current_pos++;
        }
        reverseString(s, (int)(sub_str_start - s), (int)(current_pos - s - 1));
        current_pos++;
    }
}

void reverseString(char *s, int start , int end)
{
    for ( ; start < end; start++, end--) {
        char tmp;
        tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;
    }
}

void trim(char *s)
{
    int len = strlen(s);
	char *start, *end;

	start = s;
	while (*start == ' ') {
		start++;
	}

	end = s + len - 1;
	while (*end == ' ') {
		end--;
	}

	if (start > end || start == s + len)
	{
		*s = '\0';
	} else {
		*(end + 1) = '\0';
		end = s;
		while (*start != '\0') {
			*end++ = *start++;
		}
		*(end ) = '\0';
	}
}
