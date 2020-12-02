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

int printf(const char *, ...);
int putchar(const unsigned char);
int puts(const char *);