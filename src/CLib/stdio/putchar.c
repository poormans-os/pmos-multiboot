#include "stdio.h"

//Warper function, calls terminal_putchat
int putchar(int ic)
{
    if (!ic)
        return 0;
    terminal_putchar((char)ic);
    // TODO: Implement stdio and the write system call.
    return ic;
}