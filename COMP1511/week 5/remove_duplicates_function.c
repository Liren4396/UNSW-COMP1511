//z5369144
//Liren Ding
#include <stdio.h>
int remove_duplicates(int length, int source[length], int destination[length]);

int main() {
    int arr[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int arr_2[10] = {0};
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr_2[i]);
    }
    printf("\n");
    int len = remove_duplicates(10, arr, arr_2);
    for (int i = 0; i < len; i++) {
        printf("%d ", arr_2[i]);
    }
    printf("\n");
    return 0;
}


int remove_duplicates(int length, int source[length], int destination[length]) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (source[i] == source[j]) {
                for (int k = j; k < length - 1; k++) {
                    source[k] = source[k + 1];
                }
                length--;
                j--;
            }
        }
    }
    for (int i = 0; i < length; i++) {
        destination[i] = source[i];
    }
    return length;
}