//z5369144
//Liren Ding
#include <stdio.h>
int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    int right = size - 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == i && right == j) {
                printf("*");
                right--;
            } else if (j == i) {
                printf("*");
            } else if (right == j) {
                printf("*");
                right--;
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
}