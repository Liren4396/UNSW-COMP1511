//z5369144
//Liren Ding

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *insert_nth(int n, int value, struct node *head);
struct node *create_node(int data, struct node *next);
struct node *array_to_list(int len, int array[]);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION
#define MAX_INIT_LIST_LEN 100
int main() {
    // Need to read in a number of ints into an array
    printf("How many numbers in initial list?: ");
    int list_size = 0;
    scanf("%d", &list_size);
    int initial_elems[MAX_INIT_LIST_LEN] = {0};
    int n_read = 0;
    while (n_read < list_size && scanf("%d", &initial_elems[n_read])) {
        n_read++;
    }

    // create linked list from first set of inputs
    struct node *head = NULL;
    if (n_read > 0) {
        // list has elements
        head = array_to_list(n_read, initial_elems);
    }

    printf("Enter position and value to insert: ");
    int n;
    scanf("%d", &n);
    int value;
    scanf("%d", &value);

    struct node *new_head = insert_nth(n, value, head);
    print_list(new_head);

    return 0;
}


// Insert a new node containing value at position n of the linked list.
// if n == 0, node is inserted at start of list
// if n >= length of list, node is appended at end of list
// The head of the new list is returned.
struct node *insert_nth(int n, int value, struct node *head) {
    // PUT YOUR CODE HERE! CHANGE THE NEXT LINES!

    struct node *prev = NULL;
    struct node *curr = head;

    struct node *new = malloc(sizeof (struct node));
    new->data = value;
    new->next = NULL;
    if (head == NULL) {
        return new;
    } else {
        while (curr != NULL && n >= 0) {
            //printf("%d\n", curr->data);
            if (n == 0) {
                if (prev != NULL) {
                    prev->next = new;
                    new->next = curr;
                } else {
                    new->next = curr;
                    head = new;
                }
            } else {
                prev = curr;
                curr = curr->next;
            }
            n--;
        }
        if (n >= 0) {
            prev->next = new;
        }
        return head;
    }

    
}



// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
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
