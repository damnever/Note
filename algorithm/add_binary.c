#include <stdio.h>
#include <stdlib.h>

/* https://leetcode.com/problems/add-binary/
*   a = "11", b = "1"
*   result = "100"
*  Never do *clever* thing!!!
*/

char *add_binary(char *a, char *b);

int main()
{
    printf("%s\n", add_binary("10", "1"));
    printf("%s\n", add_binary("1111", "1111"));
    return 0;
}

char *add_binary(char *a, char *b)
{
    int alen = 0, blen = 0, sum = 0;
    int len;
    char *btmp, *tmp, *bresult, *result;

    // Attention!!!
    while (*a++) alen++;
    while (*b++) blen++;
    a -= 2;
    b -= 2;
    len = alen > blen ? alen : blen;
    tmp = (char *)malloc(len*sizeof(char));
    btmp = tmp;

    while (*a || *b){
        if (*a){
            sum += *a - '0' + 0;
            a--;
        }
        if (*b){
            sum += *b - '0' + 0;
            b--;
        }
        if (sum > 1){
            *btmp++ = 3 == sum ? '1' : '0';
            sum = 1;
        }
        else {
            *btmp++ = 1 == sum ? '1' : '0';
            sum = 0;
        }
    }

    len += 1 == sum ? 1 : 0;
    result = (char *)malloc((len+1)*sizeof(char));
    bresult = result;
    if (1 == sum){
        *bresult++ = '1';
    }
    while ((--btmp) >= tmp){
        *bresult++ = *btmp;
    }
    *bresult = '\0';
    free(tmp);
    tmp = NULL;
    return result;
}
