#include <stdio.h>
#include <stdlib.h>

#define arr_len(arr) ((int)(sizeof(arr) / sizeof(*arr)))

typedef int element_t;

typedef struct _double_linked_list_node {
    struct _double_linked_list_node *prev;
    struct _double_linked_list_node *next;
    element_t value;
} node_t;

node_t *
reverse_double_linked_list(node_t *head)
{
    node_t *tail = NULL;

    while (NULL != head) {
        tail = head;
        head = head->next;
        tail->next = tail->prev;
        tail->prev = head;
    }

    return tail;
}

void
init_list(node_t **head, int *nums, int num_len)
{
    int i;
    node_t *node, *tmp;

    *head = (node_t *)malloc(sizeof(node_t));
    (*head)->prev = (*head)->next = NULL;
    (*head)->value = nums[0];
    tmp = *head;

    for (i = 1; i < num_len; ++i) {
        node = (node_t *)malloc(sizeof(node_t));
        node->value = nums[i];
        node->next = NULL;
        node->prev = tmp;
        tmp->next = node;
        tmp = tmp->next;
        node = NULL;
    }
}

void
print_list(node_t *head)
{
    while (NULL != head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int
main()
{
    node_t *head = NULL, *new_head = NULL;
    element_t nums[] = {1, 2, 3, 4, 5, 6};

    init_list(&head, nums, arr_len(nums));
    print_list(head);
    new_head = reverse_double_linked_list(head);
    print_list(new_head);

    return 0;
}
