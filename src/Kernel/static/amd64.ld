ENTRY(kernelMain)

SECTIONS {
	. = 0x0;
    /* . = 0xffffffff80000000 + 0x01000000; */
	. = 0xffffffff80100000;

	.text ALIGN(4K) : {
	    *(.text*)
	}

    .rodata ALIGN(4K) : {
        *(.rodata*)
    }

	.data ALIGN(4K) : {
	    *(.data*)
	}

	.bss ALIGN(4K) : {
		*(COMMON)
	    *(.bss*)
	}
}
