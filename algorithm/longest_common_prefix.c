#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(char **strs, int strsSize);

int main()
{
    //char **strs[3][9] = { "absdc", "abstract", "abs" };
    char* ch0 = "absdc";
    char* ch1 = "abstract";
    char* ch2 = "abs";
    char **strs = (char**)malloc(3 * sizeof(char*));
    strs[0] = ch0;
    strs[1] = ch1;
    strs[2] = ch2;
    printf("%s\n", longest_common_prefix(strs, 3));

    return 0;
}

char *longest_common_prefix(char **strs, int strsSize)
{
    int flag = 1;
    int index = 0;
    int i = 0;

    if(strsSize < 1) return "";
    if(strsSize == 1) return strs[0];

    while (*(strs[0]+index) != '\0') {
        for (i = 1; i < strsSize; i++) {
            
            if (*(strs[i] + index) != *(strs[0] + index)) {
                flag = 0;
            }
        }
        if (flag == 1) {
            index++;
        }
        else {
            break;
        }
    }

    char *result = (char*)malloc(index*sizeof(char) + 1);
    memset(result, 0, index*sizeof(char));
    for (i = 0; i < index; i++) {
        result[i] = *(strs[0] + i);
    }
    result[index] = '\0';
    return result;
}