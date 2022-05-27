//z5369144
//Liren Ding
#include <stdio.h>
int main() {
    int num_1, num_2;
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &num_1);
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &num_2);
    if (num_1 > 0 && num_2 > 0) {
        printf("Your dice range is %d to %d.\n", num_2, num_1 * num_2);
        printf("The average value is %lf\n", (num_1 * num_2 + num_2) * 1.0 / 2);
    } else {
        printf("These dice will not produce a range.\n");
    }
}