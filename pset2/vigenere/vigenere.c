/*  vigenere.c
*   Programm by Serhii Sydorenko
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // check not NULL argument
    if ( argc != 2 )
    {
        printf("fail\n");
        return 1;
    }
    
    int len = strlen(argv[1]);
    string key = argv[1];
    
    // check isalpha each char
    for (int count = 0; count < len; count++)
    {
        if (!isalpha(key[count]))
        {
            printf("fail\n");
            return 1; 
        }
    }
    
    printf("plaintext: ");
    string text = get_string();

    if (text != NULL)
    {
        printf("ciphertext: ");
        for (int i = 0, t = strlen(text), j = 0; i < t; i++, j = (j + 1) % len)
        {
            // set key lower position
            int key_low = tolower(key[j]);
            
            // Check the text of the letters and upper letters
            if (isalpha(text[i]) && isupper(text[i]))
            {
                int code_text = ((text[i] - 'A' + (key_low - 'a')) % 26) + 'A';
                printf("%c", (char) code_text);
                
                // Check the text of the letters and lower letters
            } else if (isalpha(text[i]) && islower(text[i])) 
            {
                int code_text = ((text[i] - 'a' + (key_low - 'a')) % 26) + 'a';
                printf("%c", (char) code_text);
            } else
            {
                int code_text = text[i];
                printf("%c", (char) code_text);
                j--;
            }
        }
        printf("\n");
    }
    return 0;
}