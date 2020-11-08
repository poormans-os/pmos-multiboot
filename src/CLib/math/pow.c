#include "math.h"

float fpow(float x, float y)
{
    float sum = 1, i = 0;
    if (y != 0)
    {
        for (i = fabs(y); i > 0; i--)
        {
            sum *= x;
        }
        if (y < 0)
        {
            return 1 / sum;
        }
    }
    return sum;
}