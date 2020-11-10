#include "stdio.h"

//Warper function, calls terminal_putchat
int putchar(int ic)
{
    terminal_putchar((char)ic);
    // TODO: Implement stdio and the write system call.
    return ic;
}