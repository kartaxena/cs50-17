#include <math.h>
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float sum = 0;
    for (int i = 0; sum <= 0; i ++) {
        if (i > 4)
            printf("Ви знущаєтеся? Негайно припиніть, це серйозне завдання!!!\n");
        if (i > 0) {
            
            if (sum < 0) 
            {
                printf("Ви ввели від'ємне число %.2f. Повторіть спробу!\n", sum);
            } else 
            {
                printf("Ви ввели нуль. Повторіть спробу!\n");
            }
        }  
        printf("Скільки у вас грошей: $ ");
        sum = get_float();
    }
    int cent_sum = (int) round(sum * 100);
    int coin = 0;
    int zalysh;
    int qout = 25;
    int dec = 10;
    int fi = 5;
    int one = 1;
    while (cent_sum > 0)
    {
    if (cent_sum >= qout)
    {
        zalysh = cent_sum % qout;
        coin = coin + (cent_sum - zalysh) / qout;
        cent_sum = zalysh; 
    }
    if (cent_sum >= dec)
    {
        zalysh = cent_sum % dec;
        coin = coin + (cent_sum - zalysh) / dec;
        cent_sum = zalysh; 
    }
    if (cent_sum >= fi)
    {
        zalysh = cent_sum % fi;
        coin = coin + (cent_sum - zalysh) / fi;
        cent_sum = zalysh; 
    }
    if (cent_sum >= one)
    {
        zalysh = cent_sum % one;
        coin = coin + (cent_sum - zalysh) / one;
        cent_sum = zalysh;
    }
    }
    printf("Ви отримали %i монет\n", coin);
}