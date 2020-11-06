#include "stdio/stdio.h"
#include "tty/tty.h"
#include "io/io.h"
#include "interrupts/idt.h"

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

	/*
	We have a problem with calling an interrupt, although we think the IDT should work
	*/

	printf("%s\n", "Hello, From P-MOS!");
}