#include "math.h"
/*
The function calculates square root of a number and returns it
float n - number to calculate its square root
*/
float sqrt(float n)
{
    if (n < 0)
        return -1;
    float x = n;
    float y = 1;
    float e = 0.000001; // e decides the accuracy level
    while (x - y > e)
    {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}