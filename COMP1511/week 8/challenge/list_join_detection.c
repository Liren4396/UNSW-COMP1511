

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_INPUT_STRING_LENGTH 1024

struct node {
    struct node *next;
    int          data;
};

int join_detection_point(struct node *first_list, struct node *second_list);
struct node *scan_in_list();
struct node *string_to_list(char *string);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    printf("Enter first list: ");
    struct node *first_list = scan_in_list();
    printf("Enter second list: ");
    struct node *second_list = scan_in_list();
    if (second_list == NULL) {
        printf("The second list will always have at least 1 element.\n");
        return 1;
    }

    printf("Which node of list 1 will the end of list 2 point at? ");
    int node_index;
    scanf("%d", &node_index);

    // Find the node we need the end of the second list to point at.
    struct node *current_node = first_list;
    int counter = 0;
    while (current_node != NULL && counter != node_index) {
        current_node = current_node->next;
        counter++;
    }

    // Find the last node of the second list to join them together
    struct node *last_node = second_list;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }

    last_node->next = current_node;

    int res = join_detection_point(first_list, second_list);
    if (res == -1) {
        printf("These lists do not join at all.\n");
    } else {
        printf("These lists join at node %d of the second list!\n", res);
    }

    return 0;
}

//
// Gets the index relative to `second_list` where `first_list` and
// `second_list` join together.
//
// Returns this index if found, otherwise return -1
//

// O(n*m)
/* int join_detection_point(struct node *first_list, struct node *second_list) {
    // TODO: Implement this function (And delete the line below)
    int flag = 0;
    struct node *curr = second_list;
    int count = 0;
    while (curr != NULL) {
        struct node *curr_1 = first_list;
        while (curr_1 != NULL) {
            if (curr->next == curr_1) {
                flag = 1;
                break;
            }
            curr_1 = curr_1->next;
        }
        if (flag != 1) {
            count++;
        }
        curr = curr->next;
    }
    count++;
    if (flag == 0) {
        return -1;
    } else {
        return count;
    }
    
} */

int join_detection_point(struct node *first_list, struct node *second_list) {
    // TODO: Implement this function (And delete the line below)
    struct node *curr_1 = first_list;
    struct node *curr_2 = second_list;
    int len_1 = 0;
    int len_2 = 0;
    while (curr_1) {
        len_1++;
        curr_1 = curr_1->next;
    }
    while (curr_2) {
        len_2++;
        curr_2 = curr_2->next;
    }
    curr_1 = first_list;
    curr_2 = second_list;
    int count = 0;
    if (len_1 < len_2) {
        for (int i = 0; i < len_2 - len_1; i++) {
            curr_2 = curr_2->next;
        }
        count = len_2 - len_1;
    } else {
        for (int i = 0; i < len_1 - len_2; i++) {
            curr_1 = curr_1->next;
            count = len_1 - len_2;
        }
    }
    while (curr_2 && curr_1) {
        if (curr_1 == curr_2) {
            return count;
        }
        count++;
        curr_1 = curr_1->next;
        curr_2 = curr_2->next;
    }
    return -1;
}


// DO NOT CHANGE THIS FUNCTION
// Handles input/output to scan in a list
struct node *scan_in_list() {
    char inputs[MAX_INPUT_STRING_LENGTH];
    char *input_res = fgets(inputs, MAX_INPUT_STRING_LENGTH, stdin);

    // create linked list input line
    struct node *head = NULL;
    if (input_res != NULL) {
        // Remove newline off string
        if (inputs[strlen(inputs) - 1] == '\n') {
            inputs[strlen(inputs) - 1] = '\0';
        }
        
        // Make sure all elements are valid
        int i = 0;
        // Flag for whether string is valid. An empty string is not valid and
        // initial value is based off that.
        int valid_string = strlen(inputs) > 0;
        while (valid_string && inputs[i] != '\0') {
            // Strings can only contain numbers/spaces
            if ((inputs[i] < '0' || inputs[i] > '9') && inputs[i] != ' ' && inputs[i] != '-') {
                valid_string = 0;
            }
            i++;
        }
        
        if (valid_string) {
            head = string_to_list(inputs);
        }
    }

    return head;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from string of ints
struct node *string_to_list(char *string) {
    struct node *head = NULL;
    struct node *tail = NULL;

    char *token = strtok(string, " ");

    while (token != NULL) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = NULL;
        n->data = atoi(token);
        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }

        token = strtok(NULL, " ");
    }   

    return head;
}
