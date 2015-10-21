#include <stdio.h>

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

void
swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void
max_heapify(int *arr, int i, int size)
{
    int left, right, largest = i;

    left = i * 2;
    right = i * 2 + 1;

    if (left < size && arr[left] > arr[i]) {
        largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (i != largest) {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, largest, size);
    }
}

void
heap_sort(int *arr, int len)
{
    int i, size;

    // build max heap
    for (i = len / 2; i >= 0; --i) {
        max_heapify(arr, i, len);
    }
    // sort
    size = len;
    for (i = len - 1; i >= 1; --i) {
        swap(&arr[0], &arr[i]);
        --size;
        max_heapify(arr, 0, size);
    }
}

void
print_arr(int *arr, int len)
{
    while ((len--) > 0) {
        printf("%d ", *arr++);
    }
    printf("\n");
}

int
main()
{
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int arr2[] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
    int len = arr_len(arr);
    int len2 = arr_len(arr2);

    print_arr(arr, len);
    heap_sort(arr, len);
    print_arr(arr, len);

    print_arr(arr2, len2);
    heap_sort(arr2, len2);
    print_arr(arr2, len2);

    return 0;
}
