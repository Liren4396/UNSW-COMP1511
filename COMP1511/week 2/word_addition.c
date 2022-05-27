//z5369144
//Liren Ding
#include <stdio.h>

int main() {
    int max = 2;
    int num;
    int num_1 = 0; 
    int num_2 = 0;
    int num_3;
    printf("Please enter two integers: ");
    for (int i = 0; i < max; i++) {
        scanf("%d", &num);
        if (i == 0) {
            num_1 = num;
        }
        if (i == 1) {
            num_2 = num;
        }
        if (num < 0) {
            printf("negative ");
            num *= -1;
        }
        switch (num) {
            case 0 : printf("zero ");
            break;
            case 1 : printf("one ");
            break;
            case 2 : printf("two ");
            break;
            case 3 : printf("three ");
            break;
            case 4 : printf("four ");
            break;
            case 5 : printf("five ");
            break;
            case 6 : printf("six ");
            break;
            case 7 : printf("seven ");
            break;
            case 8 : printf("eight ");
            break;
            case 9 : printf("nine ");
            break;
            case 10 : printf("ten ");
            break;
            default : printf("%d", num);
        }
        if (i == 0) {
            printf("+ ");
        } else if (i == 1) {
            printf("= ");
        }
        num_3 = num_1 + num_2;
    }
    if (num_3 <= 10) {
        if (num_3 < 0) {
            printf("negative ");
            num_3 *= -1;
        }
        switch (num_3) {
            case 0 : printf("zero ");
            break;
            case 1 : printf("one ");
            break;
            case 2 : printf("two ");
            break;
            case 3 : printf("three ");
            break;
            case 4 : printf("four ");
            break;
            case 5 : printf("five ");
            break;
            case 6 : printf("six ");
            break;
            case 7 : printf("seven ");
            break;
            case 8 : printf("eight ");
            break;
            case 9 : printf("nine ");
            break;
            case 10 : printf("ten ");
            break;
        }
    } else {
        printf("%d", num_1 + num_2);
    }
    printf("\n");

}
    
    