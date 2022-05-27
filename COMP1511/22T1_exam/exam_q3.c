// Starter code for exam_q3.

#include <stdio.h>
#define MAX 10000
int main(void) {
    // Add code to the main function to implement exam_q3!
    int arr[MAX];
    int count = 0;
    while (scanf("%d", &arr[count]) != EOF) {
        for (int i = 0; i < count; i++) {
            if (arr[i] == arr[count]) {
                printf("%d is repeated\n", arr[i]);
                return 0;
            }
        }
        count++;
    }
    
    return 0;
}
