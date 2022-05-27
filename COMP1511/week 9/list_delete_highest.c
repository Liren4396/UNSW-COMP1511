//z5369144
//Liren Ding

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LIST_LEN 100

struct node {
    struct node *next;
    int          data;
};

struct node *delete_highest(struct node *head);
struct node *array_to_list(int len, int array[]);
void print_list(struct node *head);
int find_max_value(struct node *curr);
// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    // scan in quantity of numbers
    printf("Total numbers in list: ");
    int list_size;
    scanf(" %d", &list_size);

    // scan numbers into array
    int n_read = 0;
    int numbers_list[MAX_LIST_LEN] = {0};
    while (n_read < list_size && scanf(" %d", &numbers_list[n_read])) {
        n_read++;
    }

    // create linked list from inputs
    struct node *head = array_to_list(n_read, numbers_list);

    struct node *new_head = delete_highest(head);
    print_list(new_head);

    return 0;
}



int find_max_value(struct node *head) {
    if (head == NULL) {
        return -1;
    }
    struct node *curr = head;
    int max = 0;
    while (curr != NULL) {
        if (curr->data > max) {
            max = curr->data;
        }
        curr = curr->next;
    }
    return max;
}

struct node *delete_same_num(struct node *head, int value) {
    if (head == NULL) {
        return NULL;
    }
    struct node *curr = head;
    struct node *prev = NULL;
    while (curr != NULL) {
        if (curr->data == value) {
            if (curr == head) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            struct node *node_free = curr;
            curr = curr->next;
            node_free->next = NULL;
            free(node_free);
            //return head;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

//
// Delete the node(s) in the list that contain the highest value
// The deleted node(s) are freed.
// The head of the list is returned.
//
struct node *delete_highest(struct node *head) {

    // PUT YOUR CODE HERE (change the next line!)
    int max = find_max_value(head);

    
    return delete_same_num(head, max);

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
        i -= 1;
    }   
    return head;
}

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
