#include <stdio.h>
#include <string.h>


/* If cmp(a, b) > 0, exchange, you can decide how to sort the elements.
 */
void bubble_sort(void *elems, size_t elem_num, size_t elem_size, int (*cmp)(void *, void *))
{
    size_t idx = 0, round = elem_num;
    void *x, *y;
    char tmp[elem_size];

    round -= 1;
    for (; round > 0;) {
        for (idx = 0; idx < round; ++idx) {
            x = (char *)elems + idx * elem_size;
            y = (char *)elems + (idx + 1) * elem_size;
            if (cmp(x, y) > 0) {
                memcpy(tmp, x, elem_size);
                memcpy(x, y, elem_size);
                memcpy(y, tmp, elem_size);
            }
        }
        round -= 1;
    }
}

int cmp_int(void *x, void *y)
{
    int v_x = *((int *)x);
    int v_y = *((int *)y);

    if (v_x > v_y) return 1;
    return -1;
}

int cmp_double(void *x, void *y)
{
    double v_x = *((double *)x);
    double v_y = *((double *)y);

    if (v_x < v_y) return 1;
    return -1;
}

int main()
{
    int idx, len;
    int elems1[] = {2, 12, 6, 3, 22, 8, 5};
    double elems2[] = {2.2, 12.2, 6.6, 22.2, 3.3, 8.7, 9.4};

    len = sizeof(elems1) / sizeof(*elems1);
    for (idx = 0; idx < len; ++idx) {
        printf("%d ", elems1[idx]);
    }
    printf("\n");
    bubble_sort(elems1, len, sizeof(int), cmp_int);
    for (idx = 0; idx < len; ++idx) {
        printf("%d ", elems1[idx]);
    }
    printf("\n");

    len = sizeof(elems2) / sizeof(*elems2);
    for (idx = 0; idx < len; ++idx) {
        printf("%f ", elems2[idx]);
    }
    printf("\n");
    bubble_sort(elems2, len, sizeof(double), cmp_double);
    for (idx = 0; idx < len; ++idx) {
        printf("%f ", elems2[idx]);
    }
    printf("\n");

    return 0;
}
