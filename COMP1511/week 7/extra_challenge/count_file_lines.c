//z5369144
//Liren Ding

#include <stdio.h>
#define MAX_LENGTH 2048

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

int main(void) {
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
    while (fgets(line, MAX_LENGTH, file) != NULL) {
        n_lines++;
    }

    printf("'%s' contains %d lines.\n", filename, n_lines);
}