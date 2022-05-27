//z5369144
//Liren Ding

#include <stdio.h>

int main()
{
    char word;
    while (scanf("%c", &word) != EOF)
    {
        if (word != ' ')
        {
            if (word != 'a' && word != 'e' && word != 'i' && word != 'o' && word != 'u')
            {
                printf("%c", word);
            }
        }
        else
        {
            printf(" ");
        }
    }
    return 0;
}