include GCC_PATH

.PHONY: all clean run

buildObj = @echo "\033[36m[Compiling]\033[0m $(1).o" && $(CC) -c src/$(1)/$(1).c -o build/$(1).o $(CFLAGS)

CC			= $(CUSTOM_GCC)/bin/i686-elf-gcc
AS			= $(CUSTOM_GCC)/bin/i686-elf-as
CFLAGS		= -ffreestanding -O2 -Wall -Wextra -std=gnu99
LDFLAGS		= -ffreestanding -O2 -nostdlib -lgcc
OBJFILES 	= build/stdio.o build/string.o build/tty.o build/kernel.o build/boot.o build/io.o build/idt.o build/interrupts.o
TARGET		= bin/P-MOS.bin

all: $(TARGET)

$(TARGET): build/ bin/ $(OBJFILES)
	@echo "\033[32m[Linking]\033[0m The Project"
	@$(CC) -T static/linker.ld $(OBJFILES) $(LDFLAGS) -o $(TARGET)

bin/:
	@mkdir -p bin

build/:
	@mkdir -p build

# FIXME - Renaming
build/interrupts.o:
	$(AS) src/interrupts/interrupts.s -o build/interrupts.o

# FIXME - Renaming
build/idt.o: src/interrupts/*.c
	$(CC) -c src/interrupts/interrupts.c -o build/idt.o $(CFLAGS)

build/io.o: src/io/*
	@echo "\033[34m[Assembling]\033[0m io.o"
	@$(AS) src/io/io.s -o build/io.o

build/boot.o: src/boot.s
	@echo "\033[34m[Assembling]\033[0m boot.o"
	@$(AS) src/boot.s --no-warn -o build/boot.o

build/kernel.o: src/kernel.c
	@echo "\033[36m[Compiling]\033[0m kernel.o"
	@$(CC) -c src/kernel.c -o build/kernel.o $(CFLAGS)

build/stdio.o: src/stdio/*.c
	$(call buildObj,stdio)

build/string.o: src/string/*.c
	$(call buildObj,string)

build/tty.o: src/tty/*.c
	$(call buildObj,tty)

clean:
	@echo "\033[33m[Cleaning up!]\033[0m"
	@rm -rf build
	@rm -rf bin

run: $(TARGET)
	@echo "\033[36m[Runing on qemu]\033[0m"
	@qemu-system-i386 -kernel $(TARGET)
