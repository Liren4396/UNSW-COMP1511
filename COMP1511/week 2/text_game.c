// My Text Game
// text_game.c
//
// This program was written by Liren Ding (z5369144)
// on 2022-2-21
//
// One line summary of what this exercise does.
// also a guess number game
// I have written this on 31 Oct 2021 in github.
// Here's the URL.
// https://github.com/Liren4396/c-c-/blob/
// main/%E7%8C%9C%E6%95%B0%E5%AD%97%E6%B8%B8%E6%88%8F

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void menu() {
	printf("---------Number guessing game between 1 and 100-----------\n");
	printf("--------------------Guess the number----------------------\n");
	printf("**************You only have five chances******************\n");
	printf("**********************************************************\n");
	printf("**************       1.New Game        *******************\n");
	printf("**************       2.Exit            *******************\n");
	printf("**********************************************************\n");
	printf("----------------------------------------------------------\n");
}
void game() {
	int count = 0;
	int number = rand() % 100 + 1;
	do {
		printf("\nChance : %d\n", 5 - count);
		printf("Enter the number:->");
		int player;
		scanf("%d", &player);
		if (player < number) {
			printf("Guess Smaller\n\n");
		} 
		else if (player > number) {
			printf("Guess Bigger\n\n");
		}
		else {
			printf("You Win\n");
			printf("The answer is %d !\n", number);
			break;
		}
		if (count == 4) {
			printf("Game Over!\n");
			printf("The answer is %d !\n", number);
			printf("you are lose!\n");
			break;
		}
		count++;
	} while (number);

}


int main(void) {
    // TODO: Put any setup code here
    // srand sentence is so important in here
    // It make the numbers truly random
    srand((unsigned int) time (NULL));
    int input = 1;
    // I think do while is better than while in this game
    // I think a exit choice is important for users to experience the game
    do {
		int number;
		menu();
		printf("Enter the number to continue[1 or 2]:->[ ]\b\b");
		scanf("%d", &number);
		switch (number) {
		    case 1:
			printf("Game Start!\n");
			game();
			break;
		    case 2:
			printf("exit\n");
			input = 0;
            break;
		    default:
			printf("sb\n");
			break;
		}

	} while (input);
    
    return 0;
}
