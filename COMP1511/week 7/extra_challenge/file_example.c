//
// Program to show how the provided example code works. Hardcoded to work with
// the single provided file.
//
// Written by Rory Golledge (z5308772) on 26-03-2022
//

#include <stdio.h>

#define MAX_LINE_LENGTH 2048

int main(void) {

    // Open "text_file.txt" for reading
    FILE *file = fopen("text_file.txt", "r");

    char line[MAX_LINE_LENGTH];

    // Hardcode line fetching for the example
    fgets(line, MAX_LINE_LENGTH, file);
    printf("%s", line);
    fgets(line, MAX_LINE_LENGTH, file);
    printf("%s", line);
    fgets(line, MAX_LINE_LENGTH, file);
    printf("%s", line);
    fgets(line, MAX_LINE_LENGTH, file);
    printf("%s", line);

    // Always a good idea to close files after use
    fclose(file);
}