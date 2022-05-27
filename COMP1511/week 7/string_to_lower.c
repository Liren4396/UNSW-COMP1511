// String to Lower
// string_to_lower.c
//
// This program was written by Liren Ding (z5369144)
// on 2022-3-29
//
// One line summary of what this exercise does.
//
#include <stdio.h>

void string_to_lower(char *string);

int main(int argc, char *argv[]) {

    char str[1024] = "Hi, mY nAmE iS sPonGEbOb sQuArePanTS.";
    string_to_lower(str);
    printf("%s\n", str);

    return 0;
}

// Convert the characters in `buffer` to lower case
void string_to_lower(char *string) {
    // YOUR CODE GOES HERE!
    while (*string) 
    {
        if (*string >= 'A' && *string <= 'Z')
        {
            *string += 32;
        }
        string++;
    }
}