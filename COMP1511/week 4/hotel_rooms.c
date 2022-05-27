// 
// Written 2022-3-10
// By z5369144 Liren Ding
//
//

#include <stdio.h>

#define MAX_ROOMS 50

struct hotel_room {
    // TODO: fill this in with the details of each hotel room
};

// Prints the room in the correct format when given the room_number
// and price of it.
void print_room(int room_number, double price);

int main(void) {
    int room;
    int room_num[MAX_ROOMS];
    double price[MAX_ROOMS];

    printf("How many rooms? ");
    // TODO: scan in how many rooms in the hotel
    scanf("%d", &room);
    printf("Enter hotel rooms:\n");
    // TODO: scan in the details of each hotel room
    for (int i = 0; i < room; i++) {
        scanf("%d %lf", &room_num[i], &price[i]);
    }
    printf("Room List:\n");
    // TODO: print all the rooms scanned in
    for (int i = 0; i < room; i++) {
        print_room(room_num[i], price[i]);
    }
    return 0;
}

// Prints the room in the correct format when given the room_number
// and price of it.
//
// Takes in:
// - `room_number` -- The hotel room's room number.
// - `price` -- How much the hotel room costs.
//
// Returns: nothing.
void print_room(int room_number, double price) {

    printf("Room %d @ $%.2lf\n", room_number, price);

    return;
}