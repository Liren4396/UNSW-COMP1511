//z5369144
//Liren Ding
#include <stdio.h>

char draw(int flag) {
    return flag % 2 == 0 ? '*' : '-';
}

int main() {
    int n;
    printf("How many boxes: ");
    scanf("%d", &n);
    int i, j;
    for (i = 0; i < 2 * n - 1; i++) {
        for (j = 0; j < 4 * n - 1; j++) {
            if (i <= j && i + j < 4 * n - 1) {
                printf("%c", draw(i));
            }
            else {
                printf("%c", draw(j));
            }
        }
        printf("\n");
    }
    for (; i < 4 * n - 1; i++) {
        for (j = 0; j < 4 * n - 1; j++) {
            if (i >= j && i + j >= 4 * n - 1) {
                printf("%c", draw(i));
            }
            else {
                printf("%c", draw(j));
            }
        }
        printf("\n");
    }
    return 0;
}