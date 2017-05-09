#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int m;
    printf("За одну хвилину користування душем, ви використовуєте 6 літрів води.\n");
    printf("Давайте вирахуємо, скільки пляшок ємністю 0.5 літра ви можете наповнити приймаючи душ.\n");
    do 
    {
        printf("Скільки хвилин ви плануєте приймати душ: ");
        m = get_int();
    }
    while (m <= 0);
    int buttles;
    int water = 6;
    buttles = m * 6 * 2;
    water = m * 6;
    printf("За %i хв. використано:\n", m);
    printf("Літри: %i\n", water);
    printf("Пляшки: %i\n", buttles);
}