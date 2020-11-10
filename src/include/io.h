//Allows the user to access the inb and outb function that are written in asm
#pragma once

extern void outb(unsigned int port, unsigned int value);
extern unsigned int inb(unsigned int port);