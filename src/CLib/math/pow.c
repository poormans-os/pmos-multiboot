#include "math.h"
/*
The function will calculate and return the value x by power y
float x - value to do power on
float y - power
*/
float fpow(float x, float y)
{
    float sum = 1, i = 0;
    if (y != 0) //if power is 0 return 1
    {
        for (i = fabs(y); i > 0; i--) //calculate power above 0
        {
            sum *= x;
        }
        if (y < 0) //calculate power below 0
        {
            return 1 / sum;
        }
    }
    return sum;
}