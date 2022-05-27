#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
void fib(int n, int prev[MAX], int curr[MAX], int next[MAX]) {


    for (int i = 3; i < n; i++) {
        int new[MAX] = { 0 };
        for (int j = 0; j < MAX; j++) {
            new[j] = curr[j] + prev[j] + next[j] + new[j];
            if (new[j] >= 10) {
                new[j + 1] = new[j + 1] + new[j] / 10;
                // printf("j + 1: %d\n", new[j + 1]);
                new[j] = new[j] % 10;
            }
        }
        //printf("new 0 :%d\n", new[0]);
        //printf("new 1 :%d\n", new[1]);
        //printf("new 2 :%d\n", new[2]);
        for (int k = 0; k < MAX; k++) {
            prev[k] = curr[k];
            curr[k] = next[k];
            next[k] = new[k];
        }
        //printf("new : %d\n", new[0]);
        //printf("prev : %d\n", prev[0]);
        //printf("curr : %d\n", curr[0]);
        //printf("next : %d\n", next[0]);
    }
}



int main(int argc, char *argv[]) {
    // your code here!

    //printf("argc = %d\n", argc);
    //printf("%s\n", *argv);
    //printf("%s\n", argv[argc - 1]);
    int num = atoi(argv[argc - 1]);
    int prev[MAX] = { 0 };
    int curr[MAX] = { 0 };
    int next[MAX] = { 0 };
    prev[0] = 1;
    curr[0] = 1;
    next[0] = 1;
    fib(num, prev, curr, next);
    /* printf("%d\n", next[0]);
    printf("%d\n", next[1]);
    printf("%d\n", next[2]); */
    for (int i = MAX - 1; i >= 0; i--) {
        if (next[i] != 0) {
            for (; i >= 0; i--) {
                printf("%d", next[i]);
            }
            
        }
    }
    printf("\n");
    return 0;
}