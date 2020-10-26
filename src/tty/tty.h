#pragma once

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);