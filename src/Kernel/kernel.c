/*The 'main' function, should initialize the terminal and the IDT*/
#include "stdio.h"
#include "tty.h"
#include "idt.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "not using a cross-compiler"
#endif

/* Only works for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();
	idt_init();

	printf("%s\n", "Hello, From P-MOS!");
	while (1)
	{
	}
}