#pragma once

#include <stddef.h>
#include "io.h"

#ifdef __cplusplus
extern "C" {
#endif

void terminal_initialize(void);
void terminal_putchar(char c);

#ifdef __cplusplus
}
#endif
