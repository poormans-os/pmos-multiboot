#include "math.h"
/*
The function will return absolute the value of a number
float a - number to return in absolute 
*/
float fabs(float a)
{
    return a < 0 ? -a : a; //return - value if value is negative
}