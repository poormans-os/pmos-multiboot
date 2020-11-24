//The 'main' function, should initialize the terminal and the IDT
#include "stdio.h"
#include "tty.h"
#include "idt.h"
#include "gdt.h"
#include "paging.h"
#include "multiboot.h"

// Only works for the 32-bit ix86 targets.
#if !defined(__i386__)
#error "needs to be compiled with a ix86-elf compiler"
#endif

multiboot_info_t *_bootInfo;

void kernel_main(void)
{
	// Initialize terminal interface
	terminal_initialize();
	gdt_install();
	idt_init();

	pageDirectory_init();
	loadPageDirectory(pageDirectory);
	enablePaging();

	printf("Running: %s on %s, Hello From P-MOS!\n", _bootInfo->cmdline, _bootInfo->boot_loader_name);

	printf("flags: %u\n", _bootInfo->flags);
	printf("mmap len: %u\n", _bootInfo->mmap_length);
	printf("mmap addr: %u%u\n", _bootInfo->mmap_addr << 32, _bootInfo->mmap_addr);
	if ((_bootInfo->mmap_addr) == 0)
	{
		printf("=0\n");
	}
	else if ((_bootInfo->mmap_addr) > 0)
	{
		printf(">0, %u\n", (_bootInfo->mmap_addr));
	}
	else if ((_bootInfo->mmap_addr) < 0)
	{
		printf("<0\n");
	}
	else
	{
		printf("non zero\n");
	}

	printf("mem_upper: %u\n", _bootInfo->mem_upper);
	printf("mem_lower: %u\n", _bootInfo->mem_lower);

	struct multiboot_mmap_entry *entry = _bootInfo->mmap_addr;
	while (entry < _bootInfo->mmap_addr + _bootInfo->mmap_length)
	{
		// do something with the entry
		entry = (struct multiboot_mmap_entry *)((unsigned int)entry + entry->size + sizeof(entry->size));
		printf("size: %u %u %u %u\n", entry->size, entry->addr, entry->len, entry->type);
	}

	while (1)
	{
	}
}