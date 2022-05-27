//z5369144
//Liren Ding
#include <stdio.h>
int main() {
    int num;
    printf("What number would you like to see: ");
    scanf("%d", &num);
    while (num > 1) {
        for (int i = 0; i < num; i++) {
            printf("*");
        }
        printf("\n");
        if (num % 2 == 0) {
            num /= 2;
        } else {
            num = num * 3 + 1;
        }
    }
}