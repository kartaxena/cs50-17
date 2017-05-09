/*  caesar.c
*   Programm by Serhii Sydorenko
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // check not NULL argument
    if ( argc != 2)
    {
        printf("fail\n");
        return 1;
    }
    
    // convert k to integer
    int key = atoi(argv[1]); 

    if (key <= 0)
    {
        printf("fail\n");
        return 1; 
    }
        
    printf("plaintext: ");
    string text = get_string();

    if (text != NULL)
    {
        printf("ciphertext: ");
        for (int i = 0, t = strlen(text); i < t; i++)
        {
            // Check the text of the letters and upper letters
            if (isalpha(text[i]) && isupper(text[i])) 
            {
                int code_text = ((text[i] - 'A' + key) % 26) + 'A';
                printf("%c", (char) code_text);
            
              // Check the text of the letters and lower letters  
            } else if (isalpha(text[i]) && islower(text[i])) 
            {
                int code_text = ((text[i] - 'a' + key) % 26) + 'a';
                printf("%c", (char) code_text);
            } else
            {
                int code_text = text[i];
                printf("%c", (char) code_text);
            }
        }
        printf("\n");
    }
    return 0;
}