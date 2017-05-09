/************************************
*Programming in C...                *
*Program by Sydorenko Serhii        *
*************************************/

#include <ctype.h>
#include <string.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string();
    
    // check name is not NULL
    if (name != NULL)
    {
        // loops for generate person’s initials
        for(int i = 0, n = strlen(name); i < n; i++)
        {
           // check first letter
            if (i == 0)
            {
                printf("%c", (char) toupper(name[i]));
            }
           // check spaces
            if (isspace(name[i])) 
            {
                i++;
                printf("%c", (char) toupper(name[i]));
            }
       }
        printf("\n");
    }
}