#include "stdio.h"

//Warper function, calls terminal_putchat
int putchar(const unsigned char ic)
{
    if (!ic)
        return 0;
    terminal_putchar(ic);
    // TODO: Implement stdio and the write system call.
    return ic;
}