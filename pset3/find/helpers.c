/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int lower = 0;
    int upper = n - 1;
  
    while(lower <= upper)
    {
        int middle = (lower + upper) / 2;
        if (values[middle] > value)
        {
            upper = middle - 1;
        } else if (values[middle] < value)
        {
            lower = middle + 1;
        } else if (values[middle] == value)
        {
            return true;
        }
    }
  
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int val_a, val_b;
    for (int i = 0; i < n - 1; i++)
    {
        if (values[i] > values[i + 1])
        {
            val_a = values[i];
            val_b = values[i + 1];
            values[i] = val_b;
            values[i + 1] = val_a;
        }
    }
    return;
}
