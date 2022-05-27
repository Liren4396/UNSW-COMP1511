#include <stdio.h>
#define MAX_LENGTH 32

void remove_newline(char input[MAX_LENGTH]) {

    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}



// You may optionally adapt the code below for this question.
//
// bubblesort rearranges an array of ints to be non-decreasing order.
// for example if  array a = {4, 3, 8, 9, 2, 3}
// after bubblesort(a, 6)  a will contain {2, 3, 3, 4, 8, 9}
// 
// You will need to modify the code below if you wish to order an arrays of a type other than int

void bubblesort(int array[], int length) {
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        int i = 1;
        while (i < length) {
            if (array[i] < array[i - 1]) {
                int tmp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = tmp;
                swapped = 1;
            }
            i = i + 1;
        }
    }
}

int main(void) {
	// PUT YOUR CODE HERE
    char filename[MAX_LENGTH];

    fgets(filename, MAX_LENGTH, stdin);
    remove_newline(filename);
    //printf("%s", filename);
    // Open the provided file
    FILE *file = fopen(filename, "r");
    printf("\n");
     // Ensure that the provided file was actually found. You do not need to do
    // this.
    if (file == NULL) {
        printf("'%s' was not found on the system\n", filename);
        return 1;
    }

    int n_lines = 0;
    char line[MAX_LENGTH];
    char arr[MAX_LENGTH];
    while (fgets(line, MAX_LENGTH, file) != NULL) {
        printf("%s", line);
        remove_newline(line);
        int len = strlen(line);
        arr[len] = 
        n_lines++;
    }
	return 0;
}