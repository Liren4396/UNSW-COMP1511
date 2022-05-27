//z5369144
//Liren Ding
#include <stdio.h>
#include <string.h>

int main()
{
    char word[1024] = "\0";
    printf("Input word: ");
    scanf("%s", word);
    printf("\n");
    printf("Word square is:\n");
    if (word[0] != '\0') 
    {
        int len = strlen(word);
        
        for (int i = 0; i < len; i++)
        {
            printf("%s\n", word);
        }
    }
    
}