#include "stdio.h"

int putchar(int ic)
{
    char c = (char)ic;
    terminal_write(&c, sizeof(c));
    // TODO: Implement stdio and the write system call.
    return ic;
}