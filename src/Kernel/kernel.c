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

// #define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

void kernelMain(FRAMEBUFFER *frameBuffer)
{
	// Initialize terminal interface
	// terminal_initialize();
	// gdt_install();
	// idt_init();

	// pageDirectory_init();
	// loadPageDirectory(pageDirectory);
	// enablePaging();

	// // printf("%s\n", mbi->cmdline);
	// // printf("%x", mbi->mmap_addr);

	// if (magic != 0x1BADB002)
	// {
	// 	printf("Magic not found\n");
	// }
	// else
	// {
	// 	printf("Magic ok\n");
	// }
	// printf("%x\n", magic);

	// //multiboot_info_t *mbi = (multiboot_info_t *)mbiAddr;
	// printf("flags = 0x%x\n", (unsigned)mbi->flags);
	// if (CHECK_FLAG(mbi->flags, 0))
	// 	printf("mem_lower = %uKB, mem_upper = %uKB\n", (unsigned)mbi->mem_lower, (unsigned)mbi->mem_upper);

	// /* Is boot_device valid? */
	// if (CHECK_FLAG(mbi->flags, 1))
	// 	printf("boot_device = 0x%x\n", (unsigned)mbi->boot_device);

	// /* Is the command line passed? */
	// if (CHECK_FLAG(mbi->flags, 9))
	// 	printf("boot_loader_name = %s\n", (char *)mbi->boot_loader_name);

	// // /* Are mods_* valid? */
	// // if (CHECK_FLAG(mbi->flags, 3))
	// // {
	// // 	multiboot_module_t *mod;
	// // 	unsigned int i;

	// // 	printf("mods_count = %d, mods_addr = 0x%x\n",
	// // 		   (int)mbi->mods_count, (int)mbi->mods_addr);
	// // 	for (i = 0, mod = (multiboot_module_t *)mbi->mods_addr;
	// // 		 i < mbi->mods_count;
	// // 		 i++, mod++)
	// // 		printf(" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
	// // 			   (unsigned)mod->mod_start,
	// // 			   (unsigned)mod->mod_end,
	// // 			   (char *)mod->cmdline);
	// // }

	// /* Bits 4 and 5 are mutually exclusive! */
	// if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5))
	// {
	// 	printf("Both bits 4 and 5 are set.\n");
	// 	return;
	// }

	// // /* Is the symbol table of a.out valid? */
	// // if (CHECK_FLAG(mbi->flags, 4))
	// // {
	// // 	multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);

	// // 	printf("multiboot_aout_symbol_table: tabsize = 0x%0x, "
	// // 		   "strsize = 0x%x, addr = 0x%x\n",
	// // 		   (unsigned)multiboot_aout_sym->tabsize,
	// // 		   (unsigned)multiboot_aout_sym->strsize,
	// // 		   (unsigned)multiboot_aout_sym->addr);
	// // }

	// // /* Is the section header table of ELF valid? */
	// // if (CHECK_FLAG(mbi->flags, 5))
	// // {
	// // 	multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);

	// // 	printf("multiboot_elf_sec: num = %u, size = 0x%x,"
	// // 		   " addr = 0x%x, shndx = 0x%x\n",
	// // 		   (unsigned)multiboot_elf_sec->num, (unsigned)multiboot_elf_sec->size,
	// // 		   (unsigned)multiboot_elf_sec->addr, (unsigned)multiboot_elf_sec->shndx);
	// // }

	// /* Are mmap_* valid? */
	// if (CHECK_FLAG(mbi->flags, 6))
	// {
	// 	struct multiboot_mmap_entry *mmap;

	// 	printf("mmap_addr = 0x%x, mmap_length = 0x%x\n",
	// 		   (unsigned)mbi->mmap_addr, (unsigned)mbi->mmap_length);
	// 	for (mmap = (struct multiboot_mmap_entry *)mbi->mmap_addr;
	// 		 (unsigned long)mmap < mbi->mmap_addr + mbi->mmap_length;
	// 		 mmap = (struct multiboot_mmap_entry *)((unsigned long)mmap + mmap->size + sizeof(mmap->size)))
	// 		printf(" size = 0x%x, base_addr = 0x%x%x,"
	// 			   " length = 0x%x%x, type = 0x%x\n",
	// 			   (unsigned)mmap->size,
	// 			   (unsigned)(mmap->addr >> 32),
	// 			   (unsigned)(mmap->addr & 0xffffffff),
	// 			   (unsigned)(mmap->len >> 32),
	// 			   (unsigned)(mmap->len & 0xffffffff),
	// 			   (unsigned)mmap->type);
	// }
	// *(int *)(heap_top) = 4;

	// printf("Running: %s on %s, Hello From P-MOS!\n", mbd->cmdline, mbd->boot_loader_name);

	// printf("heap[0]: %d\n", *(int *)(heap_top));
	// printf("heap size: %u\n", heap_top);
	// printf("%u\n", mbd->u.aout_sym.addr);
	// printf("flags: %u\n", mbd->flags);
	// printf("flags: %u\n", _mbd.flags);
	// printf("mmap len: %u\n", mbd->mmap_length);
	// printf("mmap addr: %u\n", mbd->mmap_addr);
	// printf("mmap addr: %u\n", _mbd.mmap_addr);
	// if ((_mbd.mmap_addr) == 0)
	// {
	// 	printf("=0\n");
	// }
	// else if ((mbd->mmap_addr) > 0)
	// {
	// 	printf(">0, %u\n", (mbd->mmap_addr));
	// }
	// else if ((mbd->mmap_addr) < 0)
	// {
	// 	printf("<0\n");
	// }
	// else
	// {
	// 	printf("non zero\n");
	// }

	// printf("mem_upper: %u\n", mbd->mem_upper);
	// printf("mem_lower: %u\n", mbd->mem_lower);

	// struct multiboot_mmap_entry *entry = mbd->mmap_addr;
	// while (entry < mbd->mmap_addr + mbd->mmap_length)
	// {
	// 	// do something with the entry
	// 	entry = (struct multiboot_mmap_entry *)((unsigned int)entry + entry->size + sizeof(entry->size));
	// 	printf("size: %u %u %u %u\n", entry->size, entry->addr, entry->len, entry->type);
	// }
}