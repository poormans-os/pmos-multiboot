#pragma once

//UEFI
typedef unsigned long long UINT64;
typedef unsigned int UINT32;

typedef struct FRAMEBUFFER
{
    void *BaseAddress;
    UINT64 BufferSize;
    UINT32 Width;
    UINT32 Height;
    UINT32 PixelsPerScanLine;
} FRAMEBUFFER;
//

#include <stddef.h>
#include "io.h"

void terminal_initialize(void);
void terminal_putchar(const unsigned char c);