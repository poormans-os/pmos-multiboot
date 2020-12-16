//The 'main' function, should initialize the terminal and the IDT
#include "stdio.h"
#include "tty.h"
#include "idt.h"
#include "gdt.h"
#include "paging.h"
#include "multiboot.h"

// // Only works for the 32-bit ix86 targets.
// #if !defined(__i386__)
// #error "needs to be compiled with a ix86-elf compiler"
// #endif

void kernelMain(FRAMEBUFFER *fb)
{
	int pixels = fb->Width * fb->Height;
	unsigned char *addr = (unsigned char *)fb->BaseAddress;
	unsigned char bg_color = 0xff;

	while (pixels--)
	{
		// if (fb->format == PIXEL_BGR)
		// {
		//     *addr++ = (bg_color >> 16) & 255;
		//     *addr++ = (bg_color >> 8) & 255;
		//     *addr++ = bg_color & 255;
		// }
		// else // RGB
		// {
		// *addr++ = 0xffff0000;
		*addr++ = bg_color & 255;
		*addr++ = (bg_color >> 8) & 255;
		*addr++ = (bg_color >> 16) & 255;
		// }
	}

	// Initialize terminal interface
	// terminal_initialize();
	// gdt_install();
	// idt_init();

	// pageDirectory_init();
	// loadPageDirectory(pageDirectory);
	// enablePaging();
}