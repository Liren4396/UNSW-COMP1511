//z5369144
//Liren Ding

#include <stdio.h>

int main() {
    int arr[10000];
    int electric_quantity = 0;
    int total_distance = 0;
    while (scanf("%d", &arr[total_distance]) != EOF) {
        total_distance++;
    }
    for (int i = 0; i < total_distance; i++) {
        electric_quantity += arr[i];
        if (i >= 1) {
            electric_quantity--;
        }
        
        if (electric_quantity <= 0 && i + 1 < total_distance) {
            printf("0\n");
            return 0;
        }
    }
    int count = 0;
    electric_quantity = 0;
    for (int j = 0; j < total_distance; j++) {
        
        int max = 0;
        for (int i = j; i < total_distance; i++) {
            if (arr[i] > max && electric_quantity >= i) {
                max = arr[i];
                arr[i] = 0;
            }
        }
        electric_quantity += max;
        count++;
        if (electric_quantity + 1 >= total_distance) {
            break;
        }
    }
    printf("%d\n", count);
    
}