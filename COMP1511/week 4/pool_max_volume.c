// Program that takes in an array of heights and outputs the maximum volume
// that can be held in one region between these heights.
//
// Written by YOUR-NAME (YOUR-ZID), DD-MM-YYYY

#include <stdio.h>

#define MAX_HEIGHT 200

int max_pool_volume(int length, int heights[length]);

int main(void) {
    int height;

    int heights[MAX_HEIGHT];
    int n_heights = 0;
    printf("Please enter heights: ");
    while (n_heights < MAX_HEIGHT && scanf("%d", &height) == 1) {
        heights[n_heights] = height;
        n_heights++;
    }

    printf(
        "Maximum volume of pools: %d\n",
        max_pool_volume(n_heights, heights)
    );

    return 0;
}

// Given an array `heights` of length `length`, returns the volume of the
// largest possible pool that can be formed between the heights.
int max_pool_volume(int length, int heights[length]) {
    // TODO: Complete this function
    int volume[200] = { 0 };
    int count = 0;
    int left_pos = 0;
    int left = heights[0];
    int max = 0;
    int max_height_less_than_left = 0;
    int j = 0;
    for (int i = 1; i < length; i++) {
        
        if (left > heights[i]) {
            volume[count] = volume[count] + left - heights[i];
            if (heights[i] > max_height_less_than_left) {
                max_height_less_than_left = heights[i];
                j = i;
            }
        } else {
            count++;
            left = heights[i];
            left_pos = i;
        }
        if (i == length - 1) {
            volume[count] = volume[count] - (left - max_height_less_than_left) * (j - left_pos);
            count++;
        }
    }
    for (int i = 0; i < count; i++) {
        if (volume[i] > max) {
            max = volume[i];
        }
    }
    return max;
}