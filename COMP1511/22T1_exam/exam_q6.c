#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_LEN 4096

struct card {
    int num;
    struct card *next;
};

struct card *deck_read(int player_num);
void print_deck(struct card *deck);
struct card *create_new();


int main(void) {
    struct card *player1 = deck_read(1);
    struct card *player2 = deck_read(2);

    // TODO: Fill in your code here!
    struct card *pile = create_new(-1);
    while (player1 != NULL && player2 != NULL) {
        struct card *curr_1 = player1;
        struct card *curr_2 = player2;
        if (pile->num == -1) {
            pile->num = curr_1->num;
            player1 = player1->next;
            if (player1 == NULL && player2 != NULL) {
                printf("Player 2 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player2 == NULL && player1 != NULL) {
                printf("Player 1 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            }
            struct card *new_2 = create_new(curr_2->num);
            new_2->next = pile;
            pile = new_2;
            player2 = player2->next;
            if (pile->num == pile->next->num) {
                printf("Snap! Matched card %d\n", pile->num);
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player1 == NULL && player2 != NULL) {
                printf("Player 2 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player2 == NULL && player1 != NULL) {
                printf("Player 1 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            }
        } else {
            struct card *new_1 = create_new(curr_1->num);
            new_1->next = pile;
            pile = new_1;
            player1 = player1->next;
            if (pile->num == pile->next->num) {
                printf("Snap! Matched card %d\n", pile->num);
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player1 == NULL && player2 != NULL) {
                printf("Player 2 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player2 == NULL && player1 != NULL) {
                printf("Player 1 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            }
            struct card *new_2 = create_new(curr_2->num);
            new_2->next = pile;
            pile = new_2;
            player2 = player2->next;
            if (pile->num == pile->next->num) {
                printf("Snap! Matched card %d\n", pile->num);
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player1 == NULL && player2 != NULL) {
                printf("Player 2 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            } else if (player2 == NULL && player1 != NULL) {
                printf("Player 1 has won!\n");
                printf("Player 1's deck: ");
                print_deck(player1);
                printf("Player 2's deck: ");
                print_deck(player2);
                printf("Pile: ");
                print_deck(pile);
                return 0;
            }
        }
        
        
        free(curr_1);
        free(curr_2);
        if (pile->num == pile->next->num) {
            printf("Snap! Matched card %d\n", pile->num);
            printf("Player 1's deck: ");
            print_deck(player1);
            printf("Player 2's deck: ");
            print_deck(player2);
            printf("Pile: ");
            print_deck(pile);
            return 0;
        }
    }
    
    while (pile != NULL) {

        struct card *pile_curr = pile;
        pile = pile->next;
        free(pile_curr);
        
    }
    
    return 0;
}


struct card *create_new(int val) {
    struct card *pile = malloc(sizeof(struct card));
    pile->num = val;
    pile->next = NULL;
    return pile;
}


void print_deck(struct card *deck) {
    while (deck != NULL) {
        printf("%d -> ", deck->num);
        deck = deck->next;
    }
    printf("X\n");
}

// Function to create a deck for the specified player.
// Returns a pointer to the top card in the deck.
struct card *deck_read(int player_num) {
    int num;
    printf("Enter Player %d's deck values:\n", player_num);
    struct card *head = NULL;
    struct card *tail = NULL;
    while (scanf("%d", &num) == 1) {
        if (num == -1) break;
        struct card *new_card = malloc(sizeof(struct card));
        new_card->num = num;
        new_card->next = NULL;
        if (head == NULL) {
            head = tail = new_card;
        } else {
            tail = tail->next = new_card;
        }
    }
    return head;
}
