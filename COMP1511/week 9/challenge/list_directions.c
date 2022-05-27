

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *left;
    struct node *right;
    char         data;
};

void print_list(struct node *head);
struct node *scan_in_list();

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    printf("Enter list: ");
    struct node *head = scan_in_list();
    print_list(head);
    return 0;
}

// Given the `head` of a list, prints the string it contains as well as the
// numbers of lefts/rights taken.
void print_list(struct node *head) {
    // TODO: COMPLETE THIS FUNCTION
    int left = 0;
    int right = 0;
    struct node *curr = head;
    printf("List string:   ");
    if (curr != NULL) {
        while (curr->left != NULL || curr->right != NULL) {
            printf("%c", curr->data);
            if (curr->left != NULL) {
                
                curr = curr->left;
                left++;
            } else if (curr->right != NULL) {
                curr = curr->right;
                right++;
            }
        }
        printf("%c", curr->data);
    }
    printf("\n");
    printf("#Lefts Taken: %d\n", left);
    printf("#Rights Taken: %d\n", right);
}

// Malloc's a new node given `left`, `right`, `data` values. Returns this node.
struct node *create_node(struct node *left, struct node *right, char data) {
    struct node *new = malloc(sizeof(struct node));
    new->left = left;
    new->right = right;
    new->data = data;

    return new;
}

// DO NOT CHANGE THIS FUNCTION
// Handles input/output to scan in a list
struct node *scan_in_list() {
    char data;
    char direction;

    // Head of list is NULL if no initial data is given.
    if (scanf(" %c", &data) != 1) {
        return NULL;
    }

    struct node *head = create_node(NULL, NULL, data);

    struct node *previous_node = head;
    // Loop through for every (direction, data) pair and linked up list
    while (scanf(" %c %c", &direction, &data) == 2) {
        assert(direction == 'L' || direction == 'R');

        struct node *new = create_node(NULL, NULL, data);
        if (direction == 'L') {
            previous_node->left = new;
            previous_node = previous_node->left;
        } else {
            previous_node->right = new;
            previous_node = previous_node->right;
        }
    }

    return head;
}
