//z5369144
//Liren Ding

#include <stdio.h>
int main() {
    int arr[100] = { 0 };
    int i = 0;
    printf("Enter numbers forwards:\n");
    while (scanf("%d", &arr[i]) != EOF) {
        i++;
    }
    printf("Reversed:\n");
    i--;
    while (i >= 0) {
        printf("%d\n", arr[i]);
        i--;
    }
}