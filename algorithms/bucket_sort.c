#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

typedef int element_t;

typedef struct _list_node {
    struct _list_node *next;
    element_t value;
} node_t;


void bucket_sort(int *nums, int len);
void init_node(node_t **node, element_t val);
node_t *list_insert(node_t *head, element_t val);
int max_num(int *nums, int len);
void print_arr(int *nums, int len);

int
main()
{
    int nums[] = {21, 42, 50, 17, 12, 8, 54, 33, 22, 9, 10, 12, 3};
    int len = arr_len(nums);

    print_arr(nums, len);
    bucket_sort(nums, len);
    print_arr(nums, len);

    return 0;
}


void
bucket_sort(int *nums, int len)
{
    int i, index, max;
    node_t *buckets[len], *head;
    for (i = 0; i < len; ++i) {
        buckets[i] = NULL;
    }

    // Put into bucket.
    max = max_num(nums, len) + 1;
    for (i = 0; i < len; ++i) {
        index = nums[i] * len / max;
        head = buckets[index];
        buckets[index] = list_insert(head, nums[i]);
    }

    // Back to array.
    index = 0;
    head = buckets[index];
    for (i = 0; i < len && index < len - 1; ++i) {
        while (index < len - 1 && NULL == head) {
            head = buckets[++index];
        }
        nums[i] = head->value;
        head = head->next;
    }
}

void
init_node(node_t **node, element_t val)
{
    *node = (node_t *)malloc(sizeof(node_t));
    (*node)->value = val;
    (*node)->next = NULL;
}

node_t *
list_insert(node_t *head, element_t val)
{
    node_t *prev, *curr, *node;

    init_node(&node, val);
    if (NULL == head) {
        return node;
    }

    prev = curr = head;
    while (NULL != curr && curr->value <= val) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == curr) {
        node->next = head;
        head = node;
    } else {
        prev->next = node;
        node->next = curr;
    }

    return head;
}

int
max_num(int *nums, int len)
{
    int i, maxnum = INT_MIN;

    for (i = 0; i < len; ++i) {
        if (nums[i] > maxnum) {
            maxnum = nums[i];
        }
    }
    return maxnum;
}

void
print_arr(int *nums, int len)
{
    while ((len--) > 0) {
        printf("%d ", *nums++);
    }
    printf("\n");
}
