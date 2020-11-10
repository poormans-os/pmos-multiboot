//our implementation of stdlib lybrary
#pragma once

#include "stdio.h"
#include "math.h"

#ifdef __cplusplus
extern "C" {
#endif

char *itoa(int value, char *str, int base);

#ifdef __cplusplus
}
#endif