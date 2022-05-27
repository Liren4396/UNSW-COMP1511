//
// Program to print out a linked list where each node contains an array of
// values then print out the total sum of these values.
//
// Written by Liren Ding (z5369144) on 08-04-2022
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_ELEMENTS 100

struct node {
    struct node *next;
    int          n_elements;
    int          data[MAX_ELEMENTS];
};

int total_list_sum(struct node *head);
struct node *new_node(int n_elements);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    struct node *head = NULL;
    struct node *tail = NULL;

    int n_array_elements;
    printf("How many array elements for this node? ");
    while (scanf("%d", &n_array_elements) == 1) {
        printf("Enter elements: ");

        struct node *node = new_node(n_array_elements);

        // If node is the first, we point the head at it. Otherwise, we add
        // the node after the tail.
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        printf("\nHow many array elements for this node? ");
    }
    printf("\n");

    print_list(head);
    printf("Sum: %d\n", total_list_sum(head));

    return 0;
}


//
// Print a linked list given the `head` of that list.
//
// Print occurs in the following format, depending on what nodes exist and
// the values in each array:
//
// #Elements: 3, Elements: [1, 2, 3]
// |
// v
// #Elements: 2, Elements: [1, 2]
// |
// v
// #Elements: 4, Elements: [1, 2, 3, 4]
// |
// v
// X
//
void print_list(struct node *head) {
    // TODO: Implement this function (replace the line below)
    struct node *curr = head;
    printf("Linked list:\n");
    while (curr != NULL) {
        int count = 1;
        if (curr->n_elements != 0) {
            printf("#Elements: %d, Elements: [%d", curr->n_elements, curr->data[0]);
        } else {
            printf("#Elements: 0, Elements: [");
        }
        
        for (; count < curr->n_elements; count++) {
            printf(", %d", curr->data[count]);
        }
        printf("]\n");
        printf("|\n");
        printf("v\n");
        curr = curr->next;
    }
    printf("X\n");
}

//
// Sum up all the array values in all nodes of a linked list provided by `head`.
//
// For example, if there are 3 nodes with arrays [1, 2, 3], [1, 2], [-3, 1]
// then this function should return 1 + 2 + 3 + 1 + 2 - 3 + 1 = 7
//
int total_list_sum(struct node *head) {
    // TODO: Implement this function (replace the line below)
    struct node *curr = head;
    int sum = 0;
    while (curr != NULL) {
        for (int i = 0; i < curr->n_elements; i++) {
            sum += curr->data[i];
        }
        curr = curr->next;
    }
    return sum;
}


// DO NOT CHANGE THIS FUNCTION
// create a new node and fills array elements equal to the `n_elements` provided
struct node *new_node(int n_elements) {
    struct node *node = malloc(sizeof(struct node));

    node->n_elements = n_elements;
    node->next = NULL;

    int element_index = 0;
    // Loop and add all elements to array of new node.
    while (
        element_index < n_elements &&
        scanf("%d", &node->data[element_index]) == 1
    ) {
        element_index++;
    }

    // If this assertion fails, then the required number of elements were not
    // scanned in.
    assert(element_index == n_elements);

    return node;
}
