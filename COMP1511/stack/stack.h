//This is the header file for the Stack
//This file describes the functions that should be implemented for the stack
//Sasha Vassar Week09 Lecture 15

#define MAX 100

//This function creates the initial stack, so it will return a pointer to the
//stack it has created, and we input nothing into it, as we are just creating 
//an empty stack
struct stack *create_stack(void);

//This function pushes an item onto the stack - the function does not return 
//anything, but is given the stack onto which the item is being pushed and the 
//item to be pushed
void push_stack(struct stack *s, int data);

//This function pops an item off the stack - the function returns an 
//int because it returns the value of the item it popped off and is given 
//the stack from which they will be removing the item
int pop_stack(struct stack *s);

//This function returns the size of the stack (so how many items are there
//in this stack) - this means we are returned an int. And we give the
//function the stack that we want the size of. 
int size_stack(struct stack *s);

//This function destroys the whole stack and will free the space that
//was allocated initially - the function is given the stack to destroy
//and does not return anything
void destroy_stack(struct stack *s);

//This function prints the stack
void print_stack(struct stack *s);