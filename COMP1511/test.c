#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



struct node {
    int data;
    struct node *next;
};

struct node *create_list() {
    struct node *list = malloc(sizeof(struct node));

    list->data = 0;
    list->next = malloc(sizeof(struct node));

    list->next->data = 0;
    list->next = NULL;

    return malloc(sizeof(struct node));
}

int main(void) {
    struct node *list = create_list();
    list = list->next;
    free(list);
}