#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cutils/heapq.h"

/*
 * https://leetcode.com/problems/sort-characters-by-frequency/
 */

typedef struct group {
    int num;
    char ch;
} group;

int group_cmp(void *x, void *y)
{
    group gx = *((group*)x);
    group gy = *((group*)y);

    if (gx.num > gy.num) return -1;
    return 1;
}

char* frequencySort(char* s)
{
    int map[256], cg, cc;
    memset(map, 0, 256 * sizeof(int));

    cg = cc = 0;
    for (char *sp = s; *sp != 0; ++sp) {
        cc += 1;
        int ord = (int)(*sp);
        if (map[ord] == 0) {
            cg += 1;
            map[ord] = 1;
        } else {
            map[ord] += 1;
        }
    }

    group groups[cg];
    int esize = sizeof(group);
    int gsize = 0;
    for (char *sp = s; *sp != 0; ++sp) {
        int ord = (int)(*sp);
        int n = map[ord];

        if (n == 0) continue;
        group g = {.num=n, .ch=*sp};
        heap_push(groups, &g, gsize, esize, group_cmp);
        map[ord] = 0;
        gsize += 1;
    }

    char *res = (char*)calloc(sizeof(char), cc);
    int pos = 0;
    for (; cg > 0; --cg) {
        group g;
        heap_pop(groups, &g, cg, esize, group_cmp);
        for (int i = 0; i < g.num; i++) {
            res[pos++] = g.ch;
        }
    }
    res[pos] = 0;

    return res;
}

int main()
{
    char s[] = "tree";
    printf("%s\n", frequencySort(s));

    char s1[] = "cccaaa";
    printf("%s\n", frequencySort(s1));

    return 0;
}
