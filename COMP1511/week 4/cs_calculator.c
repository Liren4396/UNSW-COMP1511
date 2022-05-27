//z5369144
//Liren Ding

#include <stdio.h>


int main() {
    char word;
    int num_1;
    int num_2;
    printf("Enter instruction: ");
    while (scanf("%c %d", &word, &num_1) != EOF) {
        if (word == 's') {
            printf("%d\n", num_1 * num_1);
            printf("Enter instruction: ");
        }
        if (word == 'p') {
            int count = 1;
            scanf("%d", &num_2);
            for (int i = 0; i < num_2; i++) {
                count *= num_1;
            }
            printf("%d\n", count);
            printf("Enter instruction: ");
        }
        getchar();
    }

}