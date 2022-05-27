// Assignment 0
// CS Bowling
// cs_bowling.c
//
// This program was written by Liren Ding (z5369144)
// on 2022-2-21
//
// program the logic for a bowling score calulator.
#include <stdio.h>
#include <stdio.h>


int main() {
    // welcome!
    printf("Welcome to CS Bowling!\n");

    // variable area
    // two score in each Frame
    int score1[10], score2[10];
    // the sum of two scores in each Frame
    int sum[10] = { 0 };
    // extra bonus for frame 10
    int extra_score = 0;
    // total_score added by all sum of frame
    int total_score = 0;


    // note : we should regard frame 1 to 10 as frame 0 to 9 here
    // because array space starts from 0
    // otherwise, Waste space.
    for (int i = 0; i < 10; i++) {


        // The first Score
        // here should be i + 1 
        printf("Frame %d, Bowl 1: ", i + 1);
        scanf("%d", &score1[i]);
        // the condition of the first score should be in [0, 10],
        // if it is 10, it will be Strikes, otherwise the first score will be 0;
        // so write if to distinguish three cases:
        // between 0 and 9  
        // ----->  nothing needs to be changed, just adding to sum after if
        // equal to 10 
        // ----> Strikes, stop starting Bowl 2 and stop the game
        // smaller than 0 or greater than 10 ,
        // the first score should be invalid and it has to be 0
        if (score1[i] >= 0 && score1[i] <= 9) {
            ;
        } else if (score1[i] == 10) {
            printf("Score for Frame: %d\n", score1[i]);
            // here should be plus directly because of continue
            sum[i] += score1[i];
            total_score += score1[i];
            // for Spare Bonuses
            if (i > 0) {
                if (sum[i - 1] == 10) {
                    total_score += score1[i];
                }
            }
            printf("Strike! Bonus for this frame is next two rolls.\n");
            continue;
        } else {
            printf("Bowl 1 invalid!\n");
            score1[i] = 0;
        }
        sum[i] += score1[i];



        // The Second Score
        printf("Frame %d, Bowl 2: ", i + 1);
        scanf("%d", &score2[i]);
        // the logic is the same as The first Score. just consider Three cases
        // case 1 : the bowl two score must be bigger than 0 
        // and smaller than valid value 10 , bowl one score
        // case 2 : when the bowl two score is 10 
        // ----> the bowl one score must be 0
        // case 3 : otherwise the bowl two is invalid
        // format is almost same as the first bowl
        // -----> this is because it looks clear and more understandable
        if (score2[i] >= 0 && score2[i] <= 10 - score1[i]) {
            ;
        } else if (score2[i] == 10 && score1[i] == 0) {
            printf("Score for Frame: %d\n", score2[i]);
            return 0;
        } else {
            printf("Bowl 2 invalid!\n");
            score2[i] = 0;
        }
        sum[i] += score2[i];



        // Finally distinguish whether the sum is between 0 and 10
        // Two cases: nested way
        // bewteen 0 and 10 ----> calculate the sum of score and print the sum.
        // equal to 10 ----> Spare!
        if (sum[i] >= 0 && sum[i] <= 10) {
            printf("Score for Frame: %d\n", sum[i]);
            if (sum[i] == 10) {
                printf("Spare! Bonus for this frame is next roll.\n");
            }
        }
        total_score += sum[i];


        // calculate strike and spare
        // preconditions : i > 0; because we didn't make space for score[-1] or sum[- 1]
        if (i > 0) {
            // priority : Srike > Spare
            // for Strike Bonuses
            // condition can't be  score1[i - 1] == 10 && i > 0, 
            // computer will read score1[i - 1] and calculate it,
            // and we don't make space for  score[i - 1], 
            // so it will cause (array) index out of bounds,so do sum[i - 1] !!!
            if (score1[i - 1] == 10) {
                total_score += score1[i] + score2[i];
                // for Spare Bonuses
                // else if (sum[i - 1] == 10 && score1[i - 1] != 10)
            } else if (sum[i - 1] == 10) {
                total_score += score1[i];
            }
        }


    }


    //case : extra bonus
    if (sum[9] == 10) {
        printf("Bonus Bowl 1: ");
        scanf("%d", &extra_score);
        //judge if extra_score is valid
        if (extra_score > 0 && extra_score <= 10) {
            //add extra_score twice
            total_score = 2 * extra_score + total_score;
        } else {
            printf("Bonus Bowl Invalid!\n");
        }
        
    }


    printf("Total Score: %d\n", total_score);
    return 0;
}