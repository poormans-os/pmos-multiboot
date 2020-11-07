#include "../stdio/stdio.h"
#include "../io/io.h"

void irq0_handler()
{
    //printf("int0!\n");
    outb(0x20, 0x20);
}

void irq1_handler()
{
    inb(0x60);
    //printf("int1! %d\n", inb(0x60));
    outb(0x20, 0x20);
}