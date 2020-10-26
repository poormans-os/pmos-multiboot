CUSTOM_GCC=/mnt/d/coding/os/barebones/utils/opt/cross

CC=$(CUSTOM_GCC)/bin/i686-elf-gcc
AS=$(CUSTOM_GCC)/bin/i686-elf-as

GCC_FLAGS=-ffreestanding -O2 -Wall -Wextra -std=gnu99
LIKER_FLAGS=-ffreestanding -O2 -nostdlib -lgcc

OUTPUT=bin/myos.bin

all: $(OUTPUT)

$(OUTPUT): kernel.o stdio.o string.o tty.o boot.o
	mkdir -p bin
	$(CC) -T static/linker.ld build/*.o $(LIKER_FLAGS) -o $(OUTPUT)

build: 
	mkdir -p build

kernel.o: build
	$(CC) -c src/kernel.c -o build/kernel.o $(GCC_FLAGS)

stdio.o: build
	$(CC) -c src/stdio/stdio.c -o build/stdio.o $(GCC_FLAGS)

string.o: build
	$(CC) -c src/string/string.c -o build/string.o $(GCC_FLAGS)

tty.o: build
	$(CC) -c src/tty/tty.c -o build/tty.o $(GCC_FLAGS)

boot.o: build
	$(AS) src/boot.s -o build/boot.o

clean:
	rm -rf build
	rm -rf bin

run: $(OUTPUT)
	qemu-system-i386 -kernel $(OUTPUT)
