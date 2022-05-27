//z5369144
//Liren Ding
#include <stdio.h>
int main() {
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    int i = 0;
    if (num > 0) {
        while (i <= num) {
            printf("%d\n", i);
            i++;
        }
    } else if (num < 0) {
        while (i >= num) {
            printf("%d\n", i);
            i--;
        }
    } else {
        printf("0\n");
    }
}