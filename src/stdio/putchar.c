#include "stdio.h"

int putchar(int ic)
{
    terminal_putchar((char)ic);
    // TODO: Implement stdio and the write system call.
    return ic;
}