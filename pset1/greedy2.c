#include <math.h>
#include <cs50.h>
#include <stdio.h>


int count_coins(int c, int co, int c_sum)
{
    int zalysh;
    zalysh = c_sum % c;
    co = co + (c_sum - zalysh) / c;
    c_sum = zalysh;
    return c;
    return co;
    return c_sum;
}

int main(void)
{
    float sum = 0;
    int coin = 0;
    do {
        printf("Скільки у вас грошей: $");
        sum = get_float();
        printf("%.2f\n", sum);
    }
    while (sum <= 0);
    int cent_sum = (int) round(sum * 100);
    printf("Ваша сумма в центах: %i\n", cent_sum);
    //int zalysh;
    int qout = 25;
    int dec = 10;
    int fi = 5;
    int one = 1;
    //while (cent_sum > 0)
    //{
        if (cent_sum >= qout)
            {
                count_coins(qout, coin, cent_sum);
                printf("%i %i %i\n", qout, coin, cent_sum);
            }
        if (cent_sum >= dec)
        {
            count_coins(dec, coin, cent_sum);
            printf("%i %i %i\n", dec, coin, cent_sum);
        }
        if (cent_sum >= fi)
        {
            count_coins(fi, coin, cent_sum);
            printf("%i %i %i\n", fi, coin, cent_sum); 
        }
        if (cent_sum >= one)
        {
            count_coins(one, coin, cent_sum);
         printf("%i %i %i\n", one, coin, cent_sum);
        }
        
        
        
        
        
        
    //}
    printf("Ви використали %i монет\n", coin);
    
    
}