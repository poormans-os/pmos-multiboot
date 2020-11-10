//our implementation of stdio lybrary
#pragma once

#include "string.h"
#include "tty.h"
#include "stdlib.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#define EOF (-1)

int printf(const char *__restrict, ...);
int putchar(int);
int puts(const char *);
