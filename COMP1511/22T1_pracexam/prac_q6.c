#include <stdio.h>
#include <stdlib.h>

typedef char datatype;

// Define the stack structure itself, the stack structure in this case 
// may have a size and a top node (which is the head)
struct stack {
    int size;
    struct node *top;
};

// Define each element of a stack as a node
struct node {
    datatype data;
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

void push_stack(struct stack *s, datatype item) {
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
datatype pop_stack(struct stack *s) {
    // TODO: Boundary case: what happens if the stack is empty? This means
    // there is nothing to pop off
    if (s->size == 0) {
        printf("There is nothing to pop off the stack, stack is empty\n");
        return 1;
    }
    
    // TODO: change the top node in the stack to prepare for popping the 
    // head off
    struct node *popped_head = s->top;
    datatype popped_number = popped_head->data;
    s->top = s->top->next;
    s->size = s->size - 1;
    
    // TODO: Deallocate the memory that was occupied by the node you are popping
    free(popped_head);
    return popped_number;
}

void destroy_stack(struct stack *s){
    //TODO: condition for traversing though the list to destroy?
    while (s->size != 0){
        pop_stack(s);
    }
    //TODO: Now that all the nodes are freed and deallocated, need 
    // to deallocate the actual stack structure
    free(s);
}
// Function to quickly check the size of the stack
int size_stack(struct stack *s) {
    // What should we return to give the size of the stack?
    return s->size;
};


int main(void) {
    struct stack *stack_1 = create_stack();

    datatype word;
    // read
    while (scanf("%c", &word) != EOF) {
        if (word == '{') {
            push_stack(stack_1, '{');
        } else if (word == '(') {
            push_stack(stack_1, '(');
        } else if (word == '[') {
            push_stack(stack_1, '[');
        } else if (word == '<') {
            push_stack(stack_1, '<');
        }
        if (word == '}') {
            if (size_stack(stack_1) == 0) {
                printf("Invalid Sequence, the correct closing sequence is:\n");
                return 0;
            }
            if (stack_1->top->data == '{') {
                pop_stack(stack_1);
            } else {
                break;
            }
            
        }
        if (word == ')') {
            if (size_stack(stack_1) == 0) {
                printf("Invalid Sequence, the correct closing sequence is:\n");
                return 0;
            }
            if (stack_1->top->data == '(') {
                pop_stack(stack_1);
            } else {
                break;
            }
        }
        if (word == ']') {
            if (size_stack(stack_1) == 0) {
                printf("Invalid Sequence, the correct closing sequence is:\n");
                return 0;
            }
            if (stack_1->top->data == '[') {
                pop_stack(stack_1);
            } else {
                break;
            }
        }
        if (word == '>') {
            if (size_stack(stack_1) == 0) {
                printf("Invalid Sequence, the correct closing sequence is:\n");
                return 0;
            }
            if (stack_1->top->data == '<') {
                pop_stack(stack_1);
            } else {
                break;
            }
        }
    }
    if (size_stack(stack_1) == 0) {
        printf("Valid Sequence!\n");
    }
    if (size_stack(stack_1) > 0) {
        printf("Invalid Sequence, the correct closing sequence is:\n");
        while (size_stack(stack_1) > 0) {
            if (stack_1->top->data == '{') {
                printf("}\n");
                pop_stack(stack_1);
            } else if (stack_1->top->data == '(') {
                printf(")\n");
                pop_stack(stack_1);
            } else if (stack_1->top->data == '[') {
                printf("]\n");
                pop_stack(stack_1);
            } else if (stack_1->top->data == '<') {
                printf(">\n");
                pop_stack(stack_1);
            }
        }
        //printf("%c\n", pop_stack(stack_1));
    }
    destroy_stack(stack_1);
}
