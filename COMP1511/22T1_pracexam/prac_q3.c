#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num = 0;
    int count = 0;
    int arr[10000];
    scanf("%d", &num);
    arr[count] = num;
    count++;
    while (num) {
        scanf("%d", &num);
        arr[count] = num;
        count++;
    }
    for (int i = 0; i < count - 1; i += 2) {
        printf("%d ", arr[i]);
    }
    for (int i = 1; i < count - 1; i += 2) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
