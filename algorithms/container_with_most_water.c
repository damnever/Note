// https://leetcode.com/problems/container-with-most-water/description/

#include <stdio.h>

#define min(a, b) ({ \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b; \
    })

int maxArea(int* height, int heightSize)
{
    int l = 0, r = heightSize-1;
    int lh = height[l], rh = height[r];
    int max = 0;

    for (;l < r;) {
        int v = min(lh, rh) * (r - l);
        max = v > max ? v : max; // the max area which we can assume is (width=heightSize-1).

        // only the higher height has a chance to beat the longer width
        if (lh < rh) {
            for (l += 1; l < r; l++) {
                int h = height[l];
                if (h > lh) {
                    lh = h;
                    break;
                }
            }
        } else {
            for (r -= 1; l < r; r--) {
                int h = height[r];
                if (h > rh) {
                    rh = h;
                    break;
                }
            }
        }
    }

    return max;
}

int main()
{
    int height1[5] = {4, 9, 5, 10, 7};
    printf("%d\n", maxArea(height1, 5));
    int height2[4] = {1, 2, 4, 3};
    printf("%d\n", maxArea(height2, 4));
    int height3[7] = {2, 3, 4, 5, 18, 17, 6};
    printf("%d\n", maxArea(height3, 7));
    return 0;
}
