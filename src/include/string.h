#pragma once

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char *str);
void *memset(void *s, int c, const size_t count);
void memcpy(void *dest, void *src, const size_t n);