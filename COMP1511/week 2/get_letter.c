//z5369144
//Liren Ding
#include <stdio.h>
int main() {
    char flag;
    int num;
    char word = 'a';
    printf("Uppercase: ");
    scanf("%c", &flag);
    if (flag == 'y' || flag == 'n') {
        printf("Index: ");
        scanf("%d", &num);
        if (num >= 1 && num <= 26) {
            if (flag == 'y') {
                printf("The letter is %c\n", word + num - 32 - 1);
            } else {
                printf("The letter is %c\n", word + num - 1);
            }
        } else {
            printf("You need to enter a number between 1 and 26 inclusive\n");
            printf("Exiting the program with error code 2\n");
            return 0;
        }
    } else {
        printf("You need to enter 'y' or 'n'\n");
        printf("Exiting the program with error code 1\n");
        return 0;
    }
}