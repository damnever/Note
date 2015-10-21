#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
my_strcpy(char **des, char *src)
{
    char *tmp;
    if(NULL == src) return -1;
    *des = (char*)malloc(sizeof(char) * strlen(src));
    tmp = *des;

    while (*src != '\0') {
        *tmp++ = *src++;
    }
    *tmp = '\0';

    return 0;
}

int
my_strcpy1(char *des, char *src)
{
    if (NULL == des || NULL == src) return -1;
    while (*src != '\0') {
        *des++ = *src++;
    }
    *des = '\0';

    return 0;
}

int main()
{
    char src[] = "Hello, world";
    char *des = NULL;
    int len = strlen(src);
    char des1[len];
    while (len-- > 0) {
        des1[len] = 0;
    }


    if (0 == my_strcpy(&des, src)) {
        printf("%s\n", des);
    }

    free(des);

    if (0 == my_strcpy1(des1, src)) {
        printf("%s\n", des1);
    }

    return 0;
}
