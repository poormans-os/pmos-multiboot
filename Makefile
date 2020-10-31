CUSTOM_GCC=/mnt/d/coding/os/barebones/utils/opt/cross

.PHONY: all clean run

buildObj = $(CC) -c src/$(1)/$(1).c -o build/$(1).o $(CFLAGS)

CC			= $(CUSTOM_GCC)/bin/i686-elf-gcc
AS			= $(CUSTOM_GCC)/bin/i686-elf-as
CFLAGS		= -ffreestanding -O2 -Wall -Wextra -std=gnu99
LDFLAGS		= -ffreestanding -O2 -nostdlib -lgcc
OBJFILES 	= build/stdio.o build/string.o build/tty.o build/kernel.o build/boot.o
TARGET		= bin/myos.bin

all: $(TARGET)

$(TARGET): build/ $(OBJFILES)
	mkdir -p bin
	$(CC) -T static/linker.ld $(OBJFILES) $(LDFLAGS) -o $(TARGET)

build/:
	mkdir -p build

build/boot.o: src/boot.s
	$(AS) src/boot.s -o build/boot.o

build/kernel.o: src/kernel.c
	$(CC) -c src/kernel.c -o build/kernel.o $(CFLAGS)

build/stdio.o: src/stdio/*.c
	$(call buildObj,stdio)

build/string.o: src/string/*.c
	$(call buildObj,string)

build/tty.o: src/tty/*.c
	$(call buildObj,tty)

clean:
	rm -rf build
	rm -rf bin

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)
