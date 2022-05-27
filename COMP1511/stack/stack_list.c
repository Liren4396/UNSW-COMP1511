// This is the implementation file for stack.h
// This implementation makes a stack using linked list

// Sasha Vassar Week09 Lecture 15


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

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

// Function to quickly check the size of the stack
int size_stack(struct stack *s) {
    // What should we return to give the size of the stack?
    return s->size;
};

// Function to print the stack
void print_stack(struct stack *s) {
    //Set the current node to the head...   
    struct node *current = s->top;
    while (current != NULL){
        printf("%d\n", current->data);
        current = current->next;
    }      
}

// Function to destroy the whole stack, output is nothing since you are 
// destroying and input is the stack which you want to destroy
void destroy_stack(struct stack *s){
    //TODO: condition for traversing though the list to destroy?
    while (s->size != 0){
        pop_stack(s);
    }
    //TODO: Now that all the nodes are freed and deallocated, need 
    // to deallocate the actual stack structure
    free(s);
}


