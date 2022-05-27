#include <stdio.h>

#define size 10

int main(void) {
    int my_number = 1;

    while (my_number <= 8) {
        printf("%d\n", my_number);
        my_number *= 2;
    }

}