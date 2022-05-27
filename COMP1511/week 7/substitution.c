//z5369144
//Liren Ding

#include <stdio.h>
#include <string.h>

int encrypt(int character, char* order) 
{
    int shift = 0;
    char normal_order[27] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 27; i++)
    {
        if (character == normal_order[i] || character == normal_order[i] - 32)
        {
            shift = (order[i] - normal_order[i]);
        }
    }
    
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
    char order[27];
    printf("Enter mapping:\n");
    scanf("%s", order);
    getchar();
    char word;
    printf("Enter text:\n");
    while (scanf("%c", &word) != EOF)
    {
        if (word != ' ')
        {
            word = encrypt(word, order);
            printf("%c", word);
        }
        else
        {
            printf(" ");
        }
    }
    return 0;
}