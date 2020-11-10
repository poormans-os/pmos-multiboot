/*A simple terminal that implements the vga mode in the multiboot standard*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "string.h"
#include "../vga.h"
#include "tty.h"

static const size_t VGA_WIDTH = 80;                      //The screen width, defined by the multiboot standard
static const size_t VGA_HEIGHT = 25;                     //The screen hight, defined by the multiboot standard
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000; // The address of the 'screen', defined by the multiboot standard

static size_t terminal_row;       // The current terminal row
static size_t terminal_column;    // The current terminal column row
static uint8_t terminal_color;    // The current terminal column
static uint16_t *terminal_buffer; //The array that should be printed to the screen

//A simple function that clears the screen, and sets the terminal color to their default values
void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

//Sets the terminal color to the arg 'color'
void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

//Put a char at x,y
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

//Put the cureser at x,y
void update_cursor(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

//A warper function, manages the curser and the correct x,y values
void terminal_putchar(char c)
{
    unsigned char uc = c;

    if (uc == '\n')
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
        update_cursor(terminal_column, terminal_row);
        return;
    }

    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
    update_cursor(terminal_column, terminal_row);
}
