//The 'main' function, should initialize the terminal and the IDT
#include "stdio.h"
#include "tty.h"
#include "idt.h"
#include "gdt.h"
#include "paging.h"

// Only works for the 32-bit ix86 targets.
#if !defined(__i386__)
#error "needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	// Initialize terminal interface
	terminal_initialize();
	gdt_install();
	idt_init();

	pageDirectory_init();
	loadPageDirectory(pageDirectory);
	enablePaging();

	printf("%s\n", "Hello, From P-MOS!");
	while (1)
	{
	}
}