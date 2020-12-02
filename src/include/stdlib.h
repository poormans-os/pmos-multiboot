//our implementation of stdlib library
#pragma once

#include <stdbool.h>
#include "stdio.h"
#include "math.h"

char *itoa(int value, char *str, int base, bool uint);