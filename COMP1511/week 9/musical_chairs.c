#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

// Do not edit these structs. You may use them exactly as
// they are but you cannot make changes to them

// player in the game of chairs
struct player {
    char name[MAX_NAME_LENGTH];
};

// A node in a linked list of chairs
struct chair {
    struct player *sitting;
    struct chair *next;
};

// DECLARE ANY FUNCTIONS YOU WRITE HERE
struct chair *reverse(struct chair *head) {
    // PUT YOUR CODE HERE (change the next line!)
    if (head == NULL) {
        return NULL;
    } else {
        struct chair *prev = NULL;
        struct chair *curr = head;
        struct chair *next = curr->next;
        while (curr != NULL) {
            curr->next = prev;
            prev = curr;
            curr = next;
            if (next != NULL) {
                next = next->next;
            }
        }

        return prev;
    }
}
// Make music for a certain number of turns.
// Each turn of music makes the players move
// one chair along the list.
// After they've moved that many times, the
// first chair in the list is removed, along
// with the person sitting in it.
struct chair *make_music(int turns, struct chair *chairs) {
    // IMPLEMENT THIS FUNCTION
    if (chairs == NULL) {
        return NULL;
    }
    if (chairs->next == NULL) {
        printf("%s\n", chairs->sitting->name);
        return NULL;
    }
    // head is the new head;
    // tail is the node person has to die
    // prev is tail
    struct chair *tail = chairs;
    struct chair *prev = tail->next;
    
    // reverse list
    struct chair *head = reverse(chairs);
    // connect the head and tail to be a cycle
    tail->next = head;
    // use loop to find new head;
    for (int i = 0; i < turns; i++) {
        prev = tail;
        tail = head;
        head = head->next;
    }
    // disconnect prev and tail
    tail->next = NULL;
    prev->next = NULL;
    printf("%s\n", tail->sitting->name);
    free(tail);
    //reverse and print
    head = reverse(head);
    return head;
}

// This helper function is only for this main, but
// it may help you to both understand and test this exercise.
// You may use this function for testing, but
// YOU CANNOT CHANGE THIS FUNCTION
struct chair *be_seated(char name[MAX_NAME_LENGTH], struct chair *heir) {
    struct chair *c = malloc(sizeof(struct chair));
    c->sitting = malloc(sizeof(struct player));
    strcpy(c->sitting->name, name);
    c->next = heir;
    return c;
}

// This is a main function which could be used
// to test your make_music function.
// It will not be marked.
// Only your make_music function will be marked.
int main(void) {
    struct chair *thrones = be_seated("Robert Baratheon", NULL);
    thrones = be_seated("Cersei Lannister", thrones);
    thrones = be_seated("Joffrey Baratheon", thrones);
    thrones = be_seated("Eddard Stark", thrones);
    thrones = be_seated("Spoiler Alert", thrones);
        
    thrones = make_music(1, thrones);
    thrones = make_music(2, thrones);
    thrones = make_music(0, thrones);
    thrones = make_music(-1, thrones);

    free(thrones->sitting);
    free(thrones);
        
    return 0;
}

// DEFINE ANY FUNCTIONS YOU WRITE HERE


