#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 256


void remove_newline(char input[MAX_STRING_LEN]) {

    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}

void upper_to_lower(char input[MAX_STRING_LEN]) {
    // translate upper case to lower case
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (input[i] <= 'Z' && input[i] >= 'A') {
            input[i] += 32;
        }
    }
}
void delete_same_case(char input[MAX_STRING_LEN]) {
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; input[i]; i++) {
		for (j = k = i + 1; input[j]; j++) {
            if(input[j] != input[i]) {
                input[k++] = input[j];
            }
        }
		input[k] = '\0';
	}
}


int main(void) {
    char sentence_1[MAX_STRING_LEN];
    fgets(sentence_1, MAX_STRING_LEN, stdin);
    remove_newline(sentence_1);
    upper_to_lower(sentence_1);
    delete_same_case(sentence_1);

    char sentence_2[MAX_STRING_LEN];
    fgets(sentence_2, MAX_STRING_LEN, stdin);
    remove_newline(sentence_2);
    upper_to_lower(sentence_2);
    delete_same_case(sentence_2);

    
    int len_1 = strlen(sentence_1);
    int len_2 = strlen(sentence_2);
    int count = 0;
    for (int i = 0; i < len_1; i++) {
        for (int j = 0; j < len_2; j++) {
            if (sentence_1[i] == sentence_2[j] && sentence_1[i] != ' ') {
                count++;
            }
        }
    }
    printf("%d\n", count);
}
