#include <stdio.h>


double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int mb, me, numTotal = (nums1Size + nums2Size);
    mb = me = numTotal / 2;
    if ( numTotal % 2 == 0 ) {
        mb -= 1;
    }

    int idx = numTotal - 1, median = 0;
    nums1Size -= 1;
    nums2Size -= 1;
    while (nums1Size >= 0 && nums2Size >= 0) {
        if (idx < mb) break;
        int v1 = nums1[nums1Size], v2 = nums2[nums2Size];
        if (v1 > v2) {
            nums1Size -= 1;
            if (idx == mb || idx == me) median += v1;
        } else {
            nums2Size -= 1;
            if (idx == mb || idx == me) median += v2;
        }
        idx -= 1;
    }
    for (; idx >= mb && nums1Size >= 0; idx -= 1, nums1Size -= 1) {
        if (idx == mb || idx == me) median += nums1[nums1Size];
    }
    for (; idx >= mb && nums2Size >= 0; idx -= 1, nums2Size -= 1) {
        if (idx == mb || idx == me) median += nums2[nums2Size];
    }

    return mb == me ? median : median / 2.0;
}


int main()
{
    int nums1[] = {1, 3};
    int nums2[] = {2};
    printf("%f\n", findMedianSortedArrays(nums1, 2, nums2, 1));

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    printf("%f\n", findMedianSortedArrays(nums3, 2, nums4, 2));

    int nums5[] = {};
    int nums6[] = {2, 3};
    printf("%f\n", findMedianSortedArrays(nums5, 0, nums6, 2));


    return 0;
}
