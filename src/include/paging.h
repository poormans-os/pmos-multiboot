#pragma once

#include <stdint.h>

#define PD_ENTRIES 1024
#define PT_ENTRIES 1024

uint32_t pageDirectory[1024] __attribute__((aligned(4096)));

void pageDirectory_init();
// void pageTable_init(int flags, int tableIndex);

extern void loadPageDirectory(unsigned int *);
extern void enablePaging();