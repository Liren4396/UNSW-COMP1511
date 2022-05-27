//z5369144
//Liren Ding

#include <stdio.h>
#define X_SIZE 32
#define Y_SIZE 32
#define Z_SIZE 32
int main() 
{
    // Declaring a 3D array of integers and initialising all elements to 0
    int cube[X_SIZE][Y_SIZE][Z_SIZE] = {0};
    int len;
    printf("Please enter cube length: ");
    scanf("%d", &len);
    for (int i = 0; i < len; i++)
    {
        printf("Please enter grid %d:\n", i);
        for (int j = 0; j < len; j++)
        {
            for (int z = 0; z < len; z++)
            {
                scanf("%c", &cube[i][j][z]);
            }
        }
    }
    char arr[31];
    while (scanf("%s", arr) != EOF)
    {
        int count = 0;
        for (int i = 0; i < len; i++)
        {
            printf("Please enter grid %d:\n", i);
            for (int j = 0; j < len; j++)
            {
                for (int z = 0; z < len; z++)
                {
                    if (arr[count] == cube[i][j])
                }
            }
        }
    }

}