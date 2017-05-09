#include <math.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float sum = 0;
    
    do
    {
        printf("How much change is owed? ");
        sum = get_float();
    }
    while (sum <=0);
    
    int cent_sum = (int) round(sum * 100);
    int coin = 0;
    int zalysh;
    int qout = 25;
    int dec = 10;
    int fi = 5;
    int one = 1;
    ////////////////////////////////////calculate/////////////////////////////////
    while (cent_sum > 0)
    {
        if (cent_sum >= qout)
        {
            zalysh = cent_sum % qout;
            coin += (cent_sum - zalysh) / qout;
            cent_sum = zalysh; 
        }
        if (cent_sum >= dec)
        {
            zalysh = cent_sum % dec;
            coin += (cent_sum - zalysh) / dec;
            cent_sum = zalysh; 
        }
        if (cent_sum >= fi)
        {
            zalysh = cent_sum % fi;
            coin += (cent_sum - zalysh) / fi;
            cent_sum = zalysh; 
        }
        if (cent_sum >= one)
        {
            zalysh = cent_sum % one;
            coin += (cent_sum - zalysh) / one;
            cent_sum = zalysh;
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    printf("%i\n", coin);
}