#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the stack structure itself, the stack structure in this case 
// may have a size and a top node (which is the head)
struct stack {
    int size;
    struct node *top;
};

// Define each element of a stack as a node
struct node {
    int data;
    struct node *next;
};

// If we are creating the stack what will we return and what will be 
// the input?
struct stack *create_stack(void) {
    //Allocate some memory to the stack structure
    struct stack *new_stack = malloc(sizeof(struct stack));
    
    //Check that there was enough memory to create the stack structure
    if (new_stack == NULL){
        printf("There was not enough memory to malloc\n");
        exit(1);
    }
    
    //TODO: Initialise the stack that was created 
    new_stack->size = 0;
    new_stack->top = NULL;
    
    return new_stack;
}

// TODO: Function to push an item onto the stack, what are the 
// inputs and outputs?
void push_stack(struct stack *s, int item) {
    //Allocate some memory for the new item that you will push on
    struct node *new_node = malloc(sizeof(struct node));
    //Check if there is enough memory to make a new node
    /*if (new_node == NULL) {
        printf("There is not enough memory to create a node.\n");
        exit(1);
    }*/
    //Initialise the new node
    new_node->data = item;
    new_node->next = s->top;
    
    //Correct the stack by changing the head and size
    s->size = s->size + 1;
    s->top = new_node;
    
}

// Function to pop off the stack, so we will be returning the number
// that was popped off and giving the argument of the stack from which to pop
int pop_stack(struct stack *s) {
    // TODO: Boundary case: what happens if the stack is empty? This means
    // there is nothing to pop off
    if (s->size == 0) {
        printf("There is nothing to pop off the stack, stack is empty\n");
        return 1;
    }
    
    // TODO: change the top node in the stack to prepare for popping the 
    // head off
    struct node *popped_head = s->top;
    int popped_number = popped_head->data;
    s->top = s->top->next;
    s->size = s->size - 1;
    
    // TODO: Deallocate the memory that was occupied by the node you are popping
    free(popped_head);
    return popped_number;
}



int calculate(char *s) {
    int len = strlen(s);
    struct stack *new = create_stack();
    int tmp = 0;
    char sign = '+';
    int sum = 0;
    int j = 0;
    int i = 0;
    char new_s[len];
    for (j = 0, i = 0; j < len; j++) {
        if (s[j] != 32) {
            new_s[i] = s[j];
            i++;
        }
    }
    len = i;
    for (i = 0; i < len; i++) {
        // consider the Sequential number
        if (new_s[i] <= '9' && new_s[i] >= '0') {
            tmp = 0;
            while (i < len && new_s[i] <= '9' && new_s[i] >= '0') {
                tmp = tmp * 10 + new_s[i] - '0';
                i++;
            }
        }
        // deal with the last operator
        if (sign == '+') {
            push_stack(new, tmp);
        } else if (sign == '-') {
            push_stack(new, -tmp);
        } else if (sign == '*') {
            push_stack(new, pop_stack(new) * tmp);
        } else if (sign == '/') {
            push_stack(new, pop_stack(new) / tmp);
        }
        //record the current operator
        sign = new_s[i];
            
    }
    //print_stack(new);
    // add all of them 
    while (new->size > 0) {
        sum = sum + pop_stack(new);
    }
    return sum;
}


int main() {
    int sum = calculate("   3   *    2    +    1    ");
    printf("%d\n", sum);
}