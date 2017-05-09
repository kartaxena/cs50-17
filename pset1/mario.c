#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //int h, sp, hash, weight;
    int h;
    
    do
    {
        printf("Input height: ");
        h = get_int();
    }
    while (h < 0 || h > 23);
    ///////////////////////build pyramida//////////////////////////////////
    for (int count = 0; count < h; count ++)
    {
        for (int sp = (h - count - 1); sp > 0; sp --)
        {
            printf(" ");
        }
        for (int hash = 0; hash <= (count + 1); hash ++)
        {
            printf("#");
        }
        printf("\n");
        
    }
    ////////////////////////////////////////////////////////////////////////
}