#include "string.h"

void *memset(void *s, const int c, const size_t count)
{
    for (size_t i = 0; i < count; i++)
        ((char *)s)[i] = (char)c;
    return s;
}
