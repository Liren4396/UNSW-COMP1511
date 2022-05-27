// Find the largest sum of numbers in a z shape.

#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 100

int largest_z_sum(int size, int array[MAX_SIZE][MAX_SIZE]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    int array[MAX_SIZE][MAX_SIZE];

    // Get the array size.
    int size;
    printf("Enter 2D array side length: ");
    scanf("%d", &size);
    assert(size >= 3);

    // Scan in values for the array.
    printf("Enter 2D array values:\n");
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < size) {
            assert(scanf("%d", &array[i][j]) == 1);
            j++;
        }
        i++;
    }

    printf("The largest z sum is %d.\n", largest_z_sum(size, array));

    return 0;
}

// Return the largest sum of numbers in a z shape.
int largest_z_sum(int size, int array[MAX_SIZE][MAX_SIZE]) {
    // Put your code here.
    int max = 0;
    for (int z = 3; z <= size; z++) {
        int sum = 0;
        int zsize = size - z;
        for (int i = zsize; i < size ; i++) {
            sum = sum + array[0][i] + array[size - 1 - zsize][i];
        }
        for (int i = 1; i < size - 1 - zsize; i++) {
            sum = sum + array[i][size - 1 - i];
        }
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}
