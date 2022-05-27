//z5369144
//Liren Ding
#include <stdio.h>
int main() {
    int arr[10];
    int sum = 0;
    printf("Enter numbers: ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }
    for (int j = 0; j < 10; j++) {
        if (arr[j] > 0 && arr[j] <= 6) {
            if (arr[j] == 1) {
                sum += arr[j + 1];
            }
            sum += arr[j];
        } else {
            printf("%d is not a number on a 6-sided dice.\n", arr[j]);
            return 0;
        }
    }
    printf("The sum of dice rolls is %d.\n", sum);

}