//z5369144
//Liren Ding

#include <stdio.h>
#include <string.h>

int encrypt(int character, int shift) 
{
    if (shift > 0) {
        if ('A' <= character && character <= 'Z')
        {
            character = (character - 'A' + shift) % 26 + 'A';
        } 
        else if ('a' <= character && character <= 'z') 
        {
            character = (character - 'a' + shift) % 26 + 'a';
        } 
    } 
    else if (shift < 0)
    {
        if ('A' <= character && character <= 'Z')
        {
            character = (character - 'A' - ((-shift) % 26) + 26) % 26 + 'A';
        } 
        else if ('a' <= character && character <= 'z') 
        {
            character = (character - 'a' - ((-shift) % 26) + 26) % 26 + 'a';
        } 
    }
    
    return character;
}
int main()
{
    int len;
    scanf("%d ", &len);
    char word;
    while (scanf("%c", &word) != EOF)
    {
        if (word != ' ')
        {
            word = encrypt(word, len);
            printf("%c", word);
        }
        else
        {
            printf(" ");
        }
    }
    return 0;
}