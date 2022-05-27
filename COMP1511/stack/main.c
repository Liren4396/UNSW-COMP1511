#include <stdio.h>
#include "stack.h"

int main(void){
    struct stack *new_stack = create_stack();
    
    push_stack(new_stack, 42);
    push_stack(new_stack, 1511);
    push_stack(new_stack, 24);
    push_stack(new_stack, 3);
    push_stack(new_stack, 1);
    push_stack(new_stack, 4);

    print_stack(new_stack);
    
    printf("Popped off %d\n", pop_stack(new_stack));
    
    print_stack(new_stack);
    
    pop_stack(new_stack);
    push_stack(new_stack, 81);
    
    print_stack(new_stack);
    
    return 0;
}