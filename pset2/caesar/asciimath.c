/*
 * asciimath.c
 * by Zamyla Chan
 *
 * Calculates the addition of a char and an integer,
 * and displays both the resultant character and its
 * ASCII value.
 *
 * Usage: ./asciimath key [char]
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    if (argc != 2)
        return 1;
        
    // second command line argument is the key
    int key = atoi(argv[1]); //number

    int chr = 'd';
    
    printf("\nCalculating '%c' + %d...\n", chr, key);
    
    int result = (chr + key) % 26;
        
    printf("The ASCII value of %c is %d.\n\n", result, result);
   
    return 0;
    
}