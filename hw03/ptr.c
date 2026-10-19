#include "ptr.h"

#include <stddef.h>

void swap(float *a, float*b) 
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

int minmax(const float *a, int n, float *min, float *max) 
{
    if (a == NULL || min == NULL || max == NULL || n < 1)
    {
        return -1; // Error: invalid input
    }

    float smallest = *a;
    float largest = *a;

    for (const float *p = a + 1; p < a + n; p++) 
    {
        if (*p < smallest) 
        {
            smallest = *p;
        }
        if (*p > largest) 
        {
            largest = *p;
        }
    }

    /* Update outputs only after all all input validation and scanning*/
    *min = smallest;
    *max = largest;

    return 0; // Success
}

const float *find_above(const float *a, int n, float threshold) 
{
    if (a == NULL || n < 1) 
    {
        return NULL; // Error: invalid input
    }

    for (const float *p = a; p < a + n; p++) 
    {
        if (*p > threshold) 
        {
            return p; // Return pointer to the first value above threshold
        }
    }

    return NULL; // No value above threshold found
}

void reverse(float *a, int n)
{
    if (a == NULL || n < 2) 
    {
        return; // Error: invalid input
    }
    
    float *left = a
    float *right = a + n - 1;
   
    while (left < right) 
    {
        swap_float(left, right);
        left++;
        right--;
    }
}