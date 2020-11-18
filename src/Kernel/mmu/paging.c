#include "paging.h"

void pageDirectory_init()
{
    /* Creating page directory as an array. Each page table is 4 KB */
    
    int i = 0;
    for(i = 0; i < PD_ENTRIES; i++)
    {
        /* set flags to each page table so that:
            - Supervisor: only kernel-mode can access entries
            - Write Enabled: Kernel can write or read to page table
            - Not Present: The page table is not present (for now)
        */
        pageDirectory[i] = 0x00000002;
    }

    /* Creating a page table as an array. Each page is 4 KB */
    uint32_t pageTable[1024] __attribute__((aligned(4096)));
    for(i = 0; i < PT_ENTRIES; i++)
    {
        pageTable[i] = (i * 0x1000) | 3; /* attributes: supervisor level, read/write, present. */
    }
    pageDirectory[0] = ((unsigned int)pageTable) | 3; /* putting page in first index of page directory */
}

// void pageTable_init(int flags, int tableIndex)
// {
//     /* Creating a page table as an array. Each page is 4 KB */
//     uint32_t pageTable[1024] __attribute__((aligned(4096)));
//     for(i = 0; i < PT_ENTRIES; i++)
//     {
//         pageTable[i] = (i * 0x1000) | flags; /* attributes: supervisor level, read/write, present. */
//     }
//     pageDirectory[tableIndex] = ((unsigned int)pageTable) | flags;
// }
