#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1

#define MAX_LIST_LEN 100

struct node {
    struct node *next;
    int          data;
};

struct node *delete_range(struct node *head, int start, int end);
struct node *array_to_list(int len, int array[]);
void print_list(struct node *head);
void free_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    // get list size
    int list_size;
    printf("Total numbers: ");
    scanf(" %d", &list_size);

    // read in numbers
    int list[MAX_LIST_LEN] = {0};
    int index_count = 0;
    while (index_count < list_size && scanf(" %d", &list[index_count])) {
        index_count++;
    }

    if (index_count < list_size) {
        printf("You must enter numbers equal to the total provided.\n");
        return 1;
    }

    // create linked list from input numbers
    struct node *head = NULL;
    if (index_count > 0) {
        // list has elements
        head = array_to_list(list_size, list);
    }

    int range_start;
    int range_end;
    printf("Enter delete range: ");
    if (scanf("%d %d", &range_start, &range_end) != 2) {
        printf("You must enter both a start and an end for the range.\n");
        return 2;
    }
    
    printf("List before: ");
    print_list(head);
    struct node *new_head = delete_range(head, range_start, range_end);
    printf("List after: ");
    print_list(new_head);
    free_list(new_head);

    return 0;
}


//
// Given the head of a linked list, deletes all nodes in range `start` to `end`.
// Nodes can be identified by an "index", of which the first node has index 0.
//
// Returns the head of the list afterwards.
//
struct node *delete_range(struct node *head, int start, int end) {
    // TODO: COMPLETE THIS FUNCTION AND CHANGE THIS RETURN
    struct node *curr = head;
    struct node *prev = NULL;

    int i = 0;

    while (curr != NULL) {
        if (i >= start && i <= end) {
            if (curr == head) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            struct node *node_free = curr;
            curr = curr->next;
            node_free->next = NULL;
            free(node_free);
        } else {
            prev = curr;
            curr = curr->next;
        }
        i++;
        
    }
    return head;
}


// DO NOT CHANGE THIS FUNCTION
// create linked list from array of ints
struct node *array_to_list(int len, int array[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = array[i];
        head = n;

        i--;
    }

    return head;
}

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");

    for (struct node *n = head; n != NULL; n = n->next) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

// DO NOT CHANGE THIS FUNCTION
// free linked list
void free_list(struct node *head) {
    if (head != NULL) {
        free_list(head->next);
        free(head);
    }
}
